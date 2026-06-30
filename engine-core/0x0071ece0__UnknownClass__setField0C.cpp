// FUNC_NAME: UnknownClass::setField0C
void __thiscall UnknownClass::setField0C(int thisPtr, int value)
{
    // Offset +0x0C: likely a pointer or handle (e.g., parent object, module index)
    *(int *)(thisPtr + 0x0C) = value;
}