// FUNC_NAME: SomeClass::getFloatField
float __fastcall getFloatField(int thisPtr)
{
    return *(float *)(thisPtr + 4);
}