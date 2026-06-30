// FUNC_NAME: EARSObject::constructor
// Reconstructed constructor for EARSObject base class (EARS engine)
// Sets up two vtable pointers (multiple inheritance support) and optionally initializes via TLS memory pool.

#include <windows.h>

// Externally defined vtable pointers and TLS index
extern void* PTR_LAB_00d987cc;
extern void* PTR_LAB_00d96914;
extern DWORD DAT_01139810; // TLS index for memory pool handle

void* __thiscall EARSObject_constructor(void* this, uint8_t allocFlag) {
    void** vtablePtr = nullptr;

    // Determine location for the second vtable pointer (at offset +4)
    if (this == nullptr) {
        vtablePtr = nullptr; // Decompiled code writes to null if this==0, likely a bug or unreachable
    } else {
        vtablePtr = reinterpret_cast<void**>(reinterpret_cast<char*>(this) + 4);
    }

    // Set both vtable pointers
    *vtablePtr = &PTR_LAB_00d987cc;           // Base vtable at offset +4
    *reinterpret_cast<void**>(this) = &PTR_LAB_00d96914; // Derived vtable at offset 0

    // If allocation flag's bit 0 is set, perform additional initialization
    if ((allocFlag & 1) != 0) {
        // Retrieve memory pool handle from TLS
        TlsGetValue(DAT_01139810);

        // Call internal initialization function
        // Note: second parameter is a 16-bit value at offset 1 of the object (likely an ID)
        // Third parameter is size 0x27 (39 bytes)
        extern void FUN_00aa26e0(void* obj, uint16_t idOrSize, size_t allocSize);
        FUN_00aa26e0(this, *reinterpret_cast<uint16_t*>(reinterpret_cast<char*>(this) + 1), 0x27);
    }

    return this;
}