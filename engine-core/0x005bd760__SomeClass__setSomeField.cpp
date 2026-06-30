// FUNC_NAME: SomeClass::setSomeField
void __thiscall setSomeField(int this, undefined4 value)
{
    // +0x2c: some field (likely a pointer or integer)
    *(undefined4 *)(this + 0x2c) = value;
    return;
}