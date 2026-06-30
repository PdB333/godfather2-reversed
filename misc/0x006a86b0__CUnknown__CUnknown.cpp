// FUNC_NAME: CUnknown::CUnknown
// Address: 0x006a86b0
// Role: Constructor for a class with multiple vtable pointers, likely part of EARS framework.
//   Sets virtual function tables at offsets 0x00 and 0x0C, checks/cleans up a pointer at +0x14,
//   then re-assigns the second vtable, and conditionally calls the destructor on self if allocated.

// Note: This is a __thiscall, so the first parameter (param_1) is 'this'.
// param_2: bit 0 set indicates the object was heap-allocated and should be deleted on failure.

void* __thiscall CUnknown::CUnknown(void* this, byte allocatedFlag)
{
    // Set vtable at offset 0x00 (primary)
    *(int**)this = (int*)0x00d5d8b8;               // Primary vtable
    // Set vtable at offset 0x0C (secondary, maybe subobject)
    *(int**)((char*)this + 0x0C) = (int*)0x00d5d8b4;

    // Call some static initializer (possibly reference counting or global state)
    FUN_004086d0(&DAT_012069c4);                   // Address 0x012069c4 – static data

    // If pointer at offset 0x14 is non-zero, free it
    if (*(void**)((char*)this + 0x14) != 0) {
        FUN_004daf90(this + 5);                    // Cleanup member at +0x14 (offset 5 in int units)
    }

    // Change second vtable to a different one (construction vtable pattern)
    *(int**)((char*)this + 0x0C) = (int*)0x00d5d898;

    // Clear a global flag/variable
    DAT_011299b4 = 0;                              // Global integer at 0x011299b4

    // Another static/global initialization call
    FUN_004083d0();

    // If the object was heap-allocated, call the destructor (likely operator delete)
    if ((allocatedFlag & 1) != 0) {
        FUN_009c8eb0(this);                        // Destructor/delete
    }

    return this;
}