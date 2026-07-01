// FUNC_NAME: SomeClass::constructor
undefined4* __thiscall SomeClass::constructor(undefined4* this, byte flags)
{
    int* subObjectPtr; // pointer to sub-object at offset 0x50

    // Set vtable pointers for multiple inheritance
    *this = &PTR_FUN_00d81f80;                 // +0x00: primary vtable
    this[0xf] = &PTR_LAB_00d81f70;             // +0x3C: secondary vtable
    this[0x12] = &PTR_LAB_00d81f6c;            // +0x48: tertiary vtable

    subObjectPtr = (int*)(this + 0x14);        // +0x50: pointer to sub-object data

    // Initialize the sub-object at offset 0x50
    FUN_004086d0(subObjectPtr);

    // If the sub-object pointer was non-null, clean it up first
    if (*subObjectPtr != 0) {
        FUN_00408310(subObjectPtr);
    }

    // Clean up another sub-object at offset 0x58 if non-null
    if (this[0x16] != 0) {                     // +0x58: second sub-object pointer
        FUN_00408310(this + 0x16);
    }

    // Global initialization routine
    FUN_0046c640();

    // If the flags indicate deletion, free the object memory (size 100 bytes)
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 100);
    }

    return this;
}