// FUNC_NAME: SomeClass::SomeClassConstructor

void __thiscall SomeClass::SomeClassConstructor(int *this, int param_2)
{
    // +0x00: vtable pointer
    *this = (int)&PTR_FUN_00d57758;  // vtable for SomeClass

    // +0x04: owner/identifier
    this[1] = param_2;

    // +0x08, +0x09, +0x0A: byte flags
    *(byte *)(this + 2) = 0;      // +0x08
    *(byte *)((int)this + 9) = 0;  // +0x09
    *(byte *)((int)this + 10) = 0; // +0x0A

    // +0x0C to +0x28: eight dword fields initialized to null (8 * 4 = 32 bytes)
    // offsets: +0x0C, +0x10, +0x14, +0x18, +0x1C, +0x20, +0x24, +0x28
    this[3] = 0;
    this[4] = 0;
    this[5] = 0;
    this[6] = 0;
    this[7] = 0;
    this[8] = 0;
    this[9] = 0;
    this[10] = 0;

    return;
}