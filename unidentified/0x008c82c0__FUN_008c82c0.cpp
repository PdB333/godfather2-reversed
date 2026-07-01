// FUNC_NAME: SomeClass::getScaledValue
float __fastcall getScaledValue(int param_1)
{
    // param_1 is likely a 'this' pointer for some class
    // +0x0c: pointer to some data structure
    // +0x1dc: offset within that data structure for a float value
    // +0x24: offset within 'this' for a scaling factor
    return *(float *)(*(int *)(param_1 + 0xc) + 0x1dc) * *(float *)(param_1 + 0x24);
}