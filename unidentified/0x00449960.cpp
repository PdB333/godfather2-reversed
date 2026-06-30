// FUN_00449960: MutexManager::constructor
// This is a constructor for a class that initializes two global mutex objects and a global flag.
// The vtable is set twice: first to a base vtable (0x00e31220) and later to the derived vtable (0x00e31224).
// The parameter 'flags' controls whether the object should be freed after construction (bit 0 set).

class MutexManager {
private:
    void** __vfptr;  // +0x00 vtable pointer
public:
    void __thiscall constructor(unsigned char flags);
};

// Global mutex objects (static/global data, likely used for thread synchronization)
extern int DAT_0120e944;  // +0x00 mutex data block
extern int DAT_0120e94c;  // +0x08 mutex data block (8 bytes apart)
extern int DAT_01223440;  // global initialization flag (set to 0)

// External functions
void __cdecl initializeMutex(int* mutexData);  // FUN_00408310
void __cdecl cleanupAndDelete(void* obj);      // FUN_009c8eb0

void MutexManager::constructor(unsigned char flags) {
    // Set base vtable (temporary, possibly from base class)
    this->__vfptr = (void**)0x00e31220;

    // Initialize two mutex data blocks (adjacent in memory)
    initializeMutex(&DAT_0120e944);
    initializeMutex(&DAT_0120e94c);

    // Final vtable pointer (derived class)
    this->__vfptr = (void**)0x00e31224;

    // Clear global initialization flag
    DAT_01223440 = 0;

    // If the object was heap-allocated (flag bit 0 set), delete it after construction
    if (flags & 1) {
        cleanupAndDelete(this);
    }
}