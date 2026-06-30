// FUNC_NAME: ObjectPool::initialize

#include <cstring> // for memset

// Forward declaration of global heap manager structure
struct HeapManager {
    void* (*alloc)(size_t size, void* flags); // +0x04
};

extern HeapManager* gHeapManager; // DAT_01223518

// External lock function
void lockGlobalHeap(); // FUN_005f5910
void unlockGlobalHeap(); // likely another function not shown

class ObjectPool {
public:
    void* freeHead;       // +0x00: pointer to first free element
    void* bufferStart;    // +0x04: start of allocated buffer
    int totalCount;       // +0x08: total number of elements
    int freeCount;        // +0x0C: number of currently free elements
    int elementSize;      // +0x10: size of each element
    int flags;            // +0x14: flags (bit 0 = initialized)

    // Initialize the pool with given count, element size, and optional constructor callback.
    // Returns 1 on success, 0 on failure.
    bool initialize(int count, int elementSize, void (*constructor)()) {
        // Clear the flags
        this->flags = 0;

        // Allocate buffer for all elements
        size_t totalSize = count * elementSize;
        lockGlobalHeap();

        if (gHeapManager != nullptr && totalSize != 0) {
            struct AllocFlags {
                int align;
                int type;
                int reserved;
            } flags = { 2, 4, 0 }; // Example flags, might correspond to alignment and type

            void* buffer = gHeapManager->alloc(totalSize, &flags);
            if (buffer != nullptr) {
                this->flags |= 1; // Mark initialized
                memset(buffer, 0, totalSize);

                this->bufferStart = buffer;
                this->totalCount = count;
                this->freeCount = count;
                this->elementSize = elementSize; // stored for later use
                this->freeHead = buffer;

                // Build circular free list: each element points to the next.
                // The last element's first pointer points back to the pool object.
                char* current = static_cast<char*>(buffer);
                char* end = current + totalSize;

                for (int i = 0; i < count; ++i) {
                    char* next = current + elementSize;
                    *reinterpret_cast<void**>(current) = next; // Store next pointer

                    if (constructor != nullptr) {
                        constructor(); // Call the constructor on the element (no arguments)
                    }

                    current = next;
                }

                // Last element's first pointer points back to this pool object (circular list)
                *reinterpret_cast<void**>(end - elementSize) = this;

                return true;
            }
        }

        return false;
    }
};