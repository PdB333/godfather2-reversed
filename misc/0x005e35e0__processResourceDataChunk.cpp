// FUNC_NAME: processResourceDataChunk

#include <cstdint>

// Global state references (from game data at known addresses)
extern void* gResourceManager;   // DAT_01223508
extern void* gArrayManager;      // DAT_01223514
extern void* gGameManager;       // DAT_01223510

// External helper functions (signatures inferred from use)
extern char __cdecl registerResource(void* manager, void* resource);  // FUN_005dc510
extern void __cdecl resizeArray(int newCapacity);                     // FUN_005f0dc0
extern char __cdecl finalizeArray(void* arrayManager);                // FUN_005f0720
extern void __cdecl initSimObject(void* object);                      // FUN_004c9690
extern char __cdecl registerExtra(void* manager, void* extra);        // FUN_005de470 (manager = gResourceManager+0x48)

// Return 1 on success, 0 on failure (null input or any sub‑step failure)
char processResourceDataChunk(void* data)
{
    char retVal = 1;          // uVar4
    char overallSuccess = 1;  // local_11

    if (data == nullptr) {
        return 0;             // null -> failure
    }

    // The incoming data is expected to have a 4‑byte type field at offset 0
    int* header = (int*)data;
    if (header[0] != 0xB) {   // only handle chunk type 0xB
        return 1;             // not our type, pretend success
    }

    uint32_t count1   = header[1]; // +0x04
    uint32_t count2   = header[2]; // +0x08
    uint32_t count3   = header[3]; // +0x0C
    uint32_t hasExtra = header[4]; // +0x10

    int offset = 0x14; // header occupies 5 ints (20 bytes)

    // --- Process first array: each element is 100 bytes ---
    for (uint32_t i = 0; i < count1; i++) {
        void* element = (char*)data + offset;
        offset += 100;
        if (element == nullptr) {
            overallSuccess = 0;
        } else {
            if (!registerResource(gResourceManager, element)) {
                overallSuccess = 0;
            }
        }
    }

    // --- Process second array: each element is 0x28 bytes ---
    // Items are appended to a dynamic list in gArrayManager
    // gArrayManager has a layout like:
    //   +0x24C : pointer to array of void*
    //   +0x250 : current count
    //   +0x254 : capacity
    for (uint32_t i = 0; i < count2; i++) {
        void* element = (char*)data + offset;
        offset += 0x28;
        if (element == nullptr) {
            overallSuccess = 0;
        } else {
            int* mgr = (int*)gArrayManager;
            int capacity = mgr[0x254 / 4]; // +0x254
            int count    = mgr[0x250 / 4]; // +0x250
            if (count == capacity) {
                int newCap = (capacity == 0) ? 1 : capacity * 2;
                resizeArray(newCap);  // may relocate the array
            }
            // re‑read after potential reallocation
            int* mgrReload = (int*)gArrayManager;
            int newCount   = mgrReload[0x250 / 4];
            int** arrayPtr = (int**)mgrReload[0x24C / 4];
            if (arrayPtr != nullptr) {
                arrayPtr[newCount] = (int)element;
                mgrReload[0x250 / 4] = newCount + 1;
            }
        }
    }

    // Finalize the dynamic list (e.g. sort, build index)
    if (!finalizeArray(gArrayManager)) {
        overallSuccess = 0;
    }

    // --- Process third array: each element is 0xB0 bytes ---
    for (uint32_t i = 0; i < count3; i++) {
        void* element = (char*)data + offset;
        offset += 0xB0;
        if (element == nullptr) {
            overallSuccess = 0;
        } else {
            initSimObject(element);
        }
    }

    // --- Process an optional extra block at the end ---
    if (hasExtra != 0) {
        void* extraElem = (char*)data + offset;
        if (extraElem == nullptr) {
            overallSuccess = 0;
        } else {
            // The extra resource is registered under a sub‑manager at gResourceManager+0x48
            void* subManager = (char*)gResourceManager + 0x48;
            if (!registerExtra(subManager, extraElem)) {
                overallSuccess = 0;
            }
        }
    }

    // Finalisation step – invoke a vtable function on gGameManager at offset 0xD0
    // gGameManager is an object with a virtual table
    void** vtable = *(void***)gGameManager;
    typedef void __cdecl FinaliseFn();
    FinaliseFn* finalise = (FinaliseFn*)vtable[0xD0 / 4];
    finalise();

    return overallSuccess;
}