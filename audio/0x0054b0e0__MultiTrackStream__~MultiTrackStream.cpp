// FUNC_NAME: MultiTrackStream::~MultiTrackStream

#include <windows.h>

// Externals
extern DWORD gTlsIndex; // DAT_01139810
extern void FreeStreamBuffer(void* ptr, size_t size, int flags); // FUN_00aa26e0

extern void* const vtableBase_0x00e39c48; // &PTR_FUN_00e39c48
extern void* const vtablePurecall_0x00dcfcf4; // &PTR___purecall_00dcfcf4

class MultiTrackStream {
public:
    // Destructor
    void __thiscall ~MultiTrackStream() {
        // Set vtable to the base class destructor vtable
        this->vtable = &vtableBase_0x00e39c48;

        // +0x18: stream index / ID
        int streamIndex = *(int*)((char*)this + 0x18);

        // Check if the index is valid (not -1)
        if (streamIndex >= 0) {
            // Retrieve per-thread data (necessary for FreeStreamBuffer)
            TlsGetValue(gTlsIndex);

            // +0x10: pointer to the stream buffer
            void* bufferPtr = *(void**)((char*)this + 0x10);

            // Size = (index & 0x3FFFFFFF) * 96
            size_t bufferSize = (streamIndex & 0x3FFFFFFF) * 0x60;

            // Free the buffer with flag 0x17 (type hint or deallocation mode)
            FreeStreamBuffer(bufferPtr, bufferSize, 0x17);
        }

        // Finalize: set vtable to purecall to block further virtual calls
        this->vtable = &vtablePurecall_0x00dcfcf4;
    }

private:
    void* vtable; // +0x00
    // ... other fields (omitted for brevity)
    char _pad0x10[0x08]; // placeholder for field_0x10 and field_0x18
};