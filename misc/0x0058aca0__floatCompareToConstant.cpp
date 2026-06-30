// FUNC_NAME: floatCompareToConstant
uint floatCompareToConstant(float value)
{
    // Static constant from the data section (address 0x00e2b1a4)
    // The actual value is unknown, assumed to be some threshold or sentinel.
    static const float s_compareConstant = *(float*)0x00e2b1a4;

    if (value == s_compareConstant) {
        // If exact equality, return the integer truncation of the float.
        return (uint)(int)value;
    }

    // Otherwise, return a packed status:
    // bit0: less-than (value < constant)
    // bit1: always set (2)
    // bit2: NaN flag (either operand is NaN)
    // bit6: equality (always 0 in this branch)
    // The low byte is concatenated with in_AL (from previous context, likely zero).
    uint status = ( (value == s_compareConstant) << 6 ) |
                  ( (__isnan(value) || __isnan(s_compareConstant)) << 2 ) |
                  2U |
                  ( value < s_compareConstant );
    // The decompiler shows CONCAT11 with in_AL, but in_AL is undefined.
    // This suggests the return value's low byte is overwritten by a register.
    // For reconstruction, we assume the low byte is zero.
    return status & 0xFF;  // Only the low byte is meaningful? Actually the mask is unclear.
}