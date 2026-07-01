// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *this, byte flag)
{
    // Set primary vtable at offset 0x00
    *this = &PTR_FUN_00d7bc30;
    // Set secondary vtable at offset 0x3C (this[0x0F]) - likely for interface 1
    this[0x0F] = &PTR_LAB_00d7bc20;
    // Set secondary vtable at offset 0x48 (this[0x12]) - likely for interface 2
    this[0x12] = &PTR_LAB_00d7bc1c;

    // Initialize sub-object at offset 0x54 (this + 0x15) - likely a contained object
    initSubObjectA(this + 0x15);
    initSubObjectB(this + 0x15);

    // Perform global initialization (e.g., engine singleton setup)
    performGlobalInit();

    // If flag bit 0 is set, deallocate this object (used in placement new patterns)
    if ((flag & 1) != 0) {
        operatorDelete(this, 0x70);
    }

    return this;
}