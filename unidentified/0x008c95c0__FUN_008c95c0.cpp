// FUNC_NAME: SomeClass::getFieldAtOffset0x30
float __fastcall getFieldAtOffset0x30(int thisPtr)
{
    // +0x30: some float field (e.g., speed, scale, or time)
    return *(float *)(thisPtr + 0x30);
}