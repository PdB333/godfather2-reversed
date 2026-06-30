// FUNC_NAME: SomeClass::clearSomeFlag
void __fastcall SomeClass::clearSomeFlag(int this)
{
    // Clear bit 1 (value 2) of the flags at offset +0x1c
    *(uint *)(this + 0x1c) = *(uint *)(this + 0x1c) & 0xfffffffd;
    return;
}