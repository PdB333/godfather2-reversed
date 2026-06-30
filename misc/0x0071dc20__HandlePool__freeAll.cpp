// FUNC_NAME: HandlePool::freeAll

// Reconstructed from Ghidra at 0x0071dc20
// Clears a pool of handles (3-int structures) and returns them to a free list.
// Object layout:
//   +0x00: array of 8 Handle entries (each 12 bytes: [handle, unknown, nextFree])
//   +0x60: count of used entries (max 8)

class HandlePool {
public:
    struct Handle {
        int handle;       // +0x00: 0 if free, else a resource handle
        int unknown;      // +0x04: always zero?
        int nextFree;     // +0x08: pointer to next free handle in the freelist (global)
    };

    // Global freelist head (from DAT_00e44758)
    static int* s_freeListHead;

    // +0x00: Handle array[8]
    // +0x60: count
    int count;            // at offset +0x60

    // Clears all used handles and returns them to the freelist.
    void __thiscall freeAll() {
        if (count == 0) {
            count = 0;
            return;
        }
        if (count == 1) {
            count = 0;
            return;
        }
        unsigned int i = 0;
        Handle* pHandle = (Handle*)this; // points to start of array
        do {
            if (pHandle->handle != 0) {
                // Release the resource pointed to by handle
                FUN_004daf90(pHandle); // likely destructor or release
            }
            // Return handle to freelist
            pHandle->handle = 0;
            pHandle->unknown = 0;
            pHandle->nextFree = (int)s_freeListHead; // link to current head
            i++;
            pHandle++; // advance by 12 bytes (sizeof Handle)
        } while (i < count - 1);
        count = 0;
    }
};

// External function to release a handle (from 0x004daf90)
void FUN_004daf90(HandlePool::Handle* handle);