// FUNC_NAME: UnknownClass::setTwoFields
void __thiscall UnknownClass::setTwoFields(int this, int value1, int value2)
{
    // Store two values at offsets +0x150 and +0x154 (likely a 2D vector or similar)
    *(int *)(this + 0x150) = value1;
    *(int *)(this + 0x154) = value2;
    return;
}