// FUNC_NAME: SomeClass::releaseResources
// Address: 0x0054bcf0
// Role: Cleans up TLS-allocated data and restores vtable for a base class.
// The class appears to manage thread-local storage via a global TLS index (DAT_01139810).
// The cleanup function at 0x00aa26e0 likely deallocates or resets memory blocks of size (field18 & 0x3fffffff)*0x30 with a tag 0x17.

#include <windows.h>

// Forward declarations
extern DWORD DAT_01139810; // TLS index
extern void* PTR_LAB_00e397fc; // Intermediate vtable
extern void* PTR_LAB_00dc4710; // Final base vtable

// External helper function: likely a memory deallocation or cleanup routine.
// Parameters: base pointer, size, flags/tag (0x17)
extern void FUN_00aa26e0(void* ptr, unsigned int size, unsigned char tag);

class SomeClass {
public:
    void* vtable;       // +0x00
    int field04;        // +0x04
    int field08;        // +0x08
    int field0C;        // +0x0C
    void* field10;      // +0x10  // Pointer to TLS-allocated data
    int field14;        // +0x14
    unsigned int field18; // +0x18  // Flags/state bitfield
    // ... more members

    // __thiscall
    void releaseResources();
};

void __thiscall SomeClass::releaseResources()
{
    // Step 1: Switch vtable to an intermediate base class (e.g., for cleanup)
    this->vtable = &PTR_LAB_00e397fc;

    unsigned int flags = this->field18;  // +0x18
    if ((int)flags >= 0)  // Check sign bit (may indicate active state)
    {
        // Retrieve thread-local storage pointer
        void* tlsBase = TlsGetValue(DAT_01139810);
        if (tlsBase)
        {
            // Compute size: lower 30 bits of flags * 0x30 (likely 48-byte blocks)
            unsigned int blockSize = (flags & 0x3fffffff) * 0x30;
            // Call cleanup function on the data pointer at +0x10
            // 0x17 may be a memory pool tag or allocation type
            FUN_00aa26e0(this->field10, blockSize, 0x17);
        }
    }

    // Step 2: Restore vtable to final base class (cleanup complete)
    this->vtable = &PTR_LAB_00dc4710;
    return;
}