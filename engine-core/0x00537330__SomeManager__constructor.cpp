//FUNC_NAME: SomeManager::constructor
undefined4 * __thiscall SomeManager::constructor(undefined4 *this, byte flag) {
    undefined4 *subObjectPtr;
    int i;

    // Set initial vtable pointer (base class)
    *this = &PTR_FUN_00e38908;

    // Initialize array of 16 sub-objects (each has a vtable pointer at offset 0)
    // Sub-objects are stored at offsets 0x40, 0x57, 0x6E, ..., 0x199 (0x17 bytes apart)
    subObjectPtr = this + 0x199; // Start at last element (index 15)
    i = 0xF; // 16 elements
    do {
        subObjectPtr = subObjectPtr - 0x17; // Move to previous element (decreasing offset)
        i = i - 1;
        *subObjectPtr = &PTR_LAB_00e388f0; // Set vtable of sub-object
    } while (i >= 0);

    // Set final vtable pointer (derived class)
    *this = &PTR_LAB_00e34174;

    // If flag bit 0 is set, call base constructor or allocation routine
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}