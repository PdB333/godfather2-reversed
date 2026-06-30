// FUNC_NAME: UnknownClass::setFieldAt0xAC
void UnknownClass::setFieldAt0xAC(int value)
{
    // +0xAC: some 4-byte field (likely an integer or pointer)
    *(int*)(this + 0xAC) = value;
}