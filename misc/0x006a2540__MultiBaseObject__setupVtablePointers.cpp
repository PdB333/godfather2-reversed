// FUNC_NAME: MultiBaseObject::setupVtablePointers
void __thiscall MultiBaseObject::setupVtablePointers(void)
{
    // Set up vtable pointers for multiple base classes/interfaces
    // Each assignment is followed by a call to a base initializer (FUN_006a3720)
    // Offsets are in pointer-sized units (4 bytes each on x86)
    // +0x28 (10*4) vtable pointer for base 6
    *(void**)((char*)this + 0x28) = &PTR_FUN_00d5d3c0;
    FUN_006a3720(); // Initialize base 6

    // +0x20 (8*4) vtable pointer for base 5
    *(void**)((char*)this + 0x20) = &PTR_FUN_00d5d3c0;
    FUN_006a3720(); // Initialize base 5

    // +0x18 (6*4) vtable pointer for base 4
    *(void**)((char*)this + 0x18) = &PTR_FUN_00d5d3c0;
    FUN_006a3720(); // Initialize base 4

    // +0x10 (4*4) vtable pointer for base 3
    *(void**)((char*)this + 0x10) = &PTR_FUN_00d5d3c0;
    FUN_006a3720(); // Initialize base 3

    // +0x08 (2*4) vtable pointer for base 2
    *(void**)((char*)this + 0x08) = &PTR_FUN_00d5d3c0;
    FUN_006a3720(); // Initialize base 2

    // +0x00 vtable pointer for base 1 (primary)
    *(void**)this = &PTR_FUN_00d5d3c0;
    FUN_006a3720(); // Initialize base 1
}