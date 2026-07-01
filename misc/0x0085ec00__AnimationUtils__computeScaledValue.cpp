// FUNC_NAME: AnimationUtils::computeScaledValue
// Address: 0x0085ec00
// Role: Computes a scaled float from two uint values and a flag, using global offsets and multiplier.
// Appears to be an animation time/weight calculation utility (clamp and scale with offset).

float AnimationUtils::computeScaledValue(uint a, uint b, char flag)
{
    uint chosenValue;
    float baseOffset;

    if (b <= a)
    {
        chosenValue = b;  // clamp to lower bound
        if (flag != '\0')
        {
            baseOffset = DAT_00d5ef70;  // offset for 'active' branch
        }
        else
        {
            baseOffset = DAT_00e44564;  // offset for 'inactive' branch
        }
    }
    else
    {
        chosenValue = a;  // use current value
        baseOffset = DAT_00d5eee4;  // default offset
    }

    // Convert chosen value to float, handle negative by adding extended-precision bias
    float10 result = (float10)(int)chosenValue;
    if ((int)chosenValue < 0)
    {
        result = result + (float10)DAT_00e44578;  // 2^32 or similar bias for signed->unsigned conversion
    }

    // Scale and add offset
    return (float)(result * (float10)DAT_00d75750 + (float10)baseOffset);
}