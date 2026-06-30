// FUNC_NAME: encodeFloatToScaledInteger
void __thiscall encodeFloatToScaledInteger(byte bitCount, float value)
{
    // Compute the maximum integer representable with given bit count
    int maxInt = (1 << (bitCount & 0x1f)) - 1;
    // Scale the float (assumed in [0,1]) and round to nearest integer
    int scaledInt = (int)((float)maxInt * value + 0.5f);
    float scaledFloat = (float)scaledInt;
    // Delegate to internal encoding function (0x0064b810)
    FUN_0064b810(bitCount, &scaledFloat);
}