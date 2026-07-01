// FUNC_NAME: UnknownClass::constructor (likely EARS object initializer)
// Address: 0x008125b0

void __thiscall UnknownClass::constructor(uint flags)
{
    // Set vtable pointer
    *(void***)this = &vtableTable;  // PTR_FUN_00d72fc0

    // Set offset 0x3C (0xF * 4) to a pointer table
    *(void**)((uint)this + 0x3C) = &pointerTable1;  // PTR_LAB_00d72fb0

    // Set offset 0x48 (0x12 * 4) to another pointer table
    *(void**)((uint)this + 0x48) = &pointerTable2;  // PTR_LAB_00d72fac

    // Check flags at offset 0x50 (0x14 * 4)
    byte* flagField = (byte*)((uint)this + 0x50);

    if ((*flagField & 1) == 0) {
        // Call sub-initializer when bit 0 is clear
        subInitializePart1();  // FUN_00812200
    }

    if ((*flagField & 2) != 0) {
        // Call another sub-initializer when bit 1 is set
        subInitializePart2(0x30, (void*)((uint)this + 0x3C));  // FUN_00403720
    }

    // Global initialization
    globalInit();  // FUN_0046c640

    // If param_2 (flags) has bit 0 set, call a cleanup/reinit function
    if ((flags & 1) != 0) {
        // Possibly a placement delete or reinitialization
        placementDelete(this, 0x70);  // FUN_0043b960
    }

    return;
}