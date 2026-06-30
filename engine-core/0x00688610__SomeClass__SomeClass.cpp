// FUNC_NAME: SomeClass::SomeClass
#include <cstdint>

// Constructor for SomeClass. Sets up vtables and initializes member fields.
// Offsets are in dword units unless otherwise noted (byte offset = dword offset * 4).
// Base constructor call at 0x007268d0 is invoked with the given parameter.
void* __thiscall SomeClass::SomeClass(void* thisPtr, uint32_t baseParam) {
    // Call base class or initializer function
    FUN_007268d0(baseParam);  // likely a base constructor

    uint32_t uVar1 = DAT_00d58d0c;  // global constant

    // vtable pointers (multiple inheritance or interfaces)
    *(uintptr_t*)thisPtr = &PTR_FUN_00d58ce0;        // [0x00] primary vtable
    *(uintptr_t*)((char*)thisPtr + 0x3C) = &PTR_LAB_00d58cd0;  // [0x0F] secondary vtable or function pointer
    *(uintptr_t*)((char*)thisPtr + 0x48) = &PTR_LAB_00d58ccc;  // [0x12] tertiary
    *(uintptr_t*)((char*)thisPtr + 0x50) = &PTR_LAB_00d58cc0;  // [0x14] quaternary

    // Data members at higher offsets
    *(uint32_t*)((char*)thisPtr + 0x140) = 0;   // [0x50] some counter/flag
    *(uint32_t*)((char*)thisPtr + 0x144) = 0;   // [0x51] another int
    *(uint32_t*)((char*)thisPtr + 0x148) = uVar1; // [0x52] store global constant
    *(uint8_t*)((char*)thisPtr + 0x150)  = 0;   // [0x54] byte flag
    *(uint32_t*)((char*)thisPtr + 0x14C) = 0;   // [0x53] another int

    return thisPtr;
}