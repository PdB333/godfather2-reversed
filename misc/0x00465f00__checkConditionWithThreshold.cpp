// FUNC_NAME: checkConditionWithThreshold
bool __fastcall checkConditionWithThreshold(char comparisonType, unsigned char slotIndex, int context, int arrayOffset)
{
    // Special case: slot 0x12 returns false always (maybe invalid or reserved)
    if (slotIndex == 0x12)
        return false;

    // Compute pointer to the float value from the context and offset
    // Offset formula: (arrayOffset + 0x5AE + slotIndex * 2) * 4
    // This implies an array of 8-byte structures (2 floats per slot) starting at
    // context + (arrayOffset + 0x5AE)*4
    float* value = reinterpret_cast<float*>(
        reinterpret_cast<char*>(context) + (arrayOffset + 0x5AE + slotIndex * 2) * 4);

    // Threshold float stored at offset 0x1694 from context
    float threshold = *reinterpret_cast<float*>(reinterpret_cast<char*>(context) + 0x1694);

    if (comparisonType == 0)
    {
        // Less or equal check
        return *value <= threshold;
    }
    else if (comparisonType == 1)
    {
        // Greater than (strict) check
        float current = *value;
        return (threshold <= current) && (current != threshold);
    }

    // Unknown comparison type returns false
    return false;
}