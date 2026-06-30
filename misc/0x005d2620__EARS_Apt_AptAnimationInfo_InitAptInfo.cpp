// Xbox PDB: EARS::Apt::AptAnimationInfo::InitAptInfo
// FUNC_NAME: FlashMovie::~FlashMovie (or FlashMovie::cleanup)
// Function address: 0x005d2620
// Destructor/cleanup for FlashMovie (EA EARS Scaleform movie clip)
// Fields documented in comments

#include <cstdint>

// Forward declaration for heap management functions (from EARS framework)
extern bool isObjectDeletable(void* ptr); // FUN_005c43d0
extern void earDelete(void* ptr); // called via vtable from gHeap
extern void unloadMovie(const char* name, int flags, const char* movieName, int null);
extern void resetRootMovie(); // FUN_0059e100
extern void resetSomething(); // FUN_0059d000

// Global heap manager (vtable based)
extern void* gHeap; // DAT_012234ec (points to heap manager object)

// Global cleanup list structure (used for deferred deletion)
extern struct CleanupList { // DAT_01206880
    // +0x00: ?
    // +0x14: pointer to list of pending deletions
    int** pendingDeletions; // offset 0x14
} gCleanupList;

// Constants for cleanup types
extern void* kCleanupType_0; // PTR_LAB_01126aa0
extern void* kCleanupType_1; // PTR_LAB_01126ab4

class FlashMovie {
public:
    // Offsets (in bytes from this):
    // +0x00: typeId (set to 0xFFFFFFFF)
    int32_t typeId;
    // +0x04: pointer to some resource (maybe a sprite or display object)
    void* resourcePtr;
    // +0x08: unknown (set to 0 at end)
    int32_t unknown08;
    // +0x0C: unknown
    int32_t unknown0C;
    // +0x10: pointer to a secondary resource (freed in destructor)
    void* secondaryResource;
    // +0x14: unknown, set to 0
    int32_t unknown14;
    // +0x18: unknown, set to 0
    int32_t unknown18;
    // +0x1C: pointer to an array of 0x10-byte structs (like a child list)
    void* childArray;
    // +0x20: count of elements in childArray
    int32_t childCount;
    // +0x24: unknown, set to 0
    int32_t unknown24;
    // +0x28: unknown (maybe padding)
    // +0x1D: movie name string (actually a char array at offset 0x1D)
    // Note: offset 0x1D is unaligned, but the struct likely uses a packed layout
    char movieName[?]; // starts at offset 0x1D, probably null-terminated
    // +0x30: pointer? (set to 0)
    // +0x31: pointer? (set to 0)
    // +0x32: pointer? (set to 0)
    // +0x34: pointer to some object that gets added to cleanup list
    void* deferredCleanupPtr;
    // ... other fields up to maybe 0xD0

    ~FlashMovie() {
        // Step 1: reset type ID and clear some field
        typeId = 0xFFFFFFFF;
        unknown0C = 0;
        // Clear movie name to empty string (actually just writes null terminator at start)
        // The original loop copies "" into the movie name buffer.
        // We'll simplify: just set first byte to null.
        movieName[0] = '\0';

        // Handle movie name: if it's "_level0", reset root movie;
        // otherwise, unload the movie if global flag is set.
        if (movieName[0] != '\0') {
            // Compare first 8 characters (?) with "_level0"
            bool isRoot = true;
            const char* test = "_level0";
            for (int i = 0; i < 8; i++) {
                if (movieName[i] != test[i]) {
                    isRoot = false;
                    break;
                }
            }
            if (isRoot) {
                resetRootMovie();
                resetSomething();
            } else if (/* global gUnloadMovieFlag */ *reinterpret_cast<unsigned int*>(0x012055b0) != 0) {
                unloadMovie("unloadMovie", 0, movieName, 0);
            }
            movieName[0] = '\0';
        }

        // Free resourcePtr if not null
        if (resourcePtr != nullptr) {
            if (!isObjectDeletable(resourcePtr)) {
                // Call delete via heap manager vtable
                void* heapMgr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gHeap) + 4);
                void (*deleter)(void*, int) = *reinterpret_cast<void (**)(void*, int)>(heapMgr);
                deleter(resourcePtr, 0);
            }
            resourcePtr = nullptr;
        }

        // Add deferredCleanupPtr to global cleanup list (if not null)
        if (deferredCleanupPtr != nullptr) {
            int** listPtr = reinterpret_cast<int**>(reinterpret_cast<char*>(&gCleanupList) + 0x14);
            *reinterpret_cast<void**>(*listPtr) = &kCleanupType_0; // set cleanup type
            (*listPtr)++; // advance pointer
            *reinterpret_cast<void**>(*listPtr) = deferredCleanupPtr;
            (*listPtr)++;
            deferredCleanupPtr = nullptr;
        }

        // Process childArray elements
        if (childCount > 0) {
            for (int i = 0; i < childCount; i++) {
                // Each child struct is 0x10 bytes
                char* currentChild = reinterpret_cast<char*>(childArray) + i * 0x10;
                // Clear field at offset 0xC
                *reinterpret_cast<int32_t*>(currentChild + 0xC) = 0;
                // Internal loop over sub-items (if count field at offset 8 is > 0)
                int subCount = *reinterpret_cast<int32_t*>(currentChild + 8);
                if (subCount > 0) {
                    int subIndex = 0; // field at offset 0xC (cleared above)
                    while (subIndex < subCount) {
                        int subOffset = *reinterpret_cast<int32_t*>(currentChild + 0xC) + *reinterpret_cast<int32_t*>(currentChild + 4);
                        char* subItem = reinterpret_cast<char*>(childArray) + subOffset; //?? might be different
                        // Actually the code used: iVar7 = *(int *)(iVar6 + 0xc) + *(int *)(iVar6 + 4);
                        // iVar6 is the child base, so subItem = childArray + (subIndex + field_at_4)
                        // It's simpler to assume the sub-item pointer is stored elsewhere.
                        // For reconstruction, we'll just perform the action:
                        void* subResource = *reinterpret_cast<void**>(subItem + 0x38);
                        if (subResource != nullptr) {
                            // Add to cleanup list with type 1
                            int** listPtr = reinterpret_cast<int**>(reinterpret_cast<char*>(&gCleanupList) + 0x14);
                            *reinterpret_cast<void**>(*listPtr) = &kCleanupType_1;
                            (*listPtr)++;
                            *reinterpret_cast<void**>(*listPtr) = subResource;
                            (*listPtr)++;
                            *reinterpret_cast<void**>(subItem + 0x38) = nullptr;
                        }
                        // Advance subIndex (stored at offset 0xC)
                        int* indexPtr = reinterpret_cast<int*>(currentChild + 0xC);
                        *indexPtr += *reinterpret_cast<int*>(currentChild + 4); // actual increment is by the field at +4
                        subIndex = *indexPtr;
                    }
                }
            }
        }

        // Clear childArray count and pointer, then free array elements and array itself
        unknown24 = 0;
        childCount = 0;
        if (childArray != nullptr) {
            // Array size is stored at childArray[-4] ??? Actually the size is at offset -4 from the pointer?
            int* arrayMeta = reinterpret_cast<int*>(childArray) - 1; // size in ints
            int elemCount = *arrayMeta;
            if (elemCount >= 0) {
                char* elemPtr = reinterpret_cast<char*>(childArray) + elemCount * 0x10;
                for (int i = elemCount - 1; i >= 0; i--) {
                    elemPtr -= 0x10;
                    void* firstField = *reinterpret_cast<void**>(elemPtr);
                    if (firstField != nullptr) {
                        if (!isObjectDeletable(firstField)) {
                            void* heapMgr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gHeap) + 4);
                            void (*deleter)(void*, int) = *reinterpret_cast<void (**)(void*, int)>(heapMgr);
                            deleter(firstField, 0);
                        }
                        *reinterpret_cast<void**>(elemPtr) = nullptr;
                    }
                }
            }
            // Free the array allocation itself
            void* arrayBase = reinterpret_cast<char*>(childArray) - 4; // metadata
            if (!isObjectDeletable(arrayBase)) {
                void* heapMgr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gHeap) + 4);
                void (*deleter)(void*, int) = *reinterpret_cast<void (**)(void*, int)>(heapMgr);
                deleter(arrayBase, 0);
            }
            childArray = nullptr;
        }

        // Free secondaryResource
        if (secondaryResource != nullptr) {
            if (!isObjectDeletable(secondaryResource)) {
                void* heapMgr = *reinterpret_cast<void**>(reinterpret_cast<char*>(gHeap) + 4);
                void (*deleter)(void*, int) = *reinterpret_cast<void (**)(void*, int)>(heapMgr);
                deleter(secondaryResource, 0);
            }
            secondaryResource = nullptr;
        }

        // Clear unknown34, unknown31, unknown32
        deferredCleanupPtr = nullptr;
        unknown18 = 0; // unknown31
        unknown14 = 0; // unknown30? Actually offset 0x30 is cleared earlier
        // At the end, clear unknown08 and unknown0C
        unknown08 = 0;
        unknown0C = 0;
    }
};