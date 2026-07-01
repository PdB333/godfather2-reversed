// FUNC_NAME: SomeClass::setSomeField
void __thiscall SomeClass::setSomeField(int this, undefined4 value)
{
    // +0x6c: some field
    *(undefined4 *)(this + 0x6c) = value;
    return;
}