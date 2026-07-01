// FUNC_NAME: SomeClass::setSomeField
void __thiscall SomeClass::setSomeField(SomeClass* this, int value)
{
    // +0x80: some field
    *(int*)((char*)this + 0x80) = value;
}