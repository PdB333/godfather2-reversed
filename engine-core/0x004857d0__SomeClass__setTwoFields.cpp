// FUNC_NAME: SomeClass::setTwoFields
void __thiscall SomeClass::setTwoFields(uint32_t val1, uint32_t val2)
{
    // Store val1 at offset +0x14
    *(uint32_t *)(this + 0x14) = val1;
    // Store val2 at offset +0x1c
    *(uint32_t *)(this + 0x1c) = val2;
}