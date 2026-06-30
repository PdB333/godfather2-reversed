// FUNC_NAME: UnknownClass::isFlagSet
bool __thiscall UnknownClass::isFlagSet(void)
{
    // Check if the int at offset 0x4f8 is non-zero (likely a flag or pointer)
    return *(int *)(this + 0x4f8) != 0;
}