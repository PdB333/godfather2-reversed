// FUNC_NAME: SomeClass::getScaledValue
float __fastcall getScaledValue(int thisPtr)
{
    // +0x1D0: pointer to some sub-object (e.g., a multiplier source)
    // +0x188: base value to scale
    if (*(int *)(thisPtr + 0x1D0) != 0) {
        // +0x58: scale factor from the sub-object
        return *(float *)(*(int *)(thisPtr + 0x1D0) + 0x58) * *(float *)(thisPtr + 0x188);
    }
    return 0.0f;
}