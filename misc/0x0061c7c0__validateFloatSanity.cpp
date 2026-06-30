// FUNC_NAME: validateFloatSanity

// Global constants from Ghidra analysis (addresses commented)
extern float g_minFloatRange;       // 0x00e445bc – lower bound of acceptable range
extern float g_maxFloatRange;       // 0x00e445ac – upper bound (exclusive)
extern uint32_t g_floatBitMask;     // 0x00e44680 – bitmask for float value extraction
extern float g_expectedValue;       // 0x00e2b05c – expected masked/scaled result
extern float g_validationMultiplier; // 0x00e44728 – multiplier for second check

// Forward declaration of the assertion/error handler (0x00b99fcb)
extern void handleFloatAssertion();

void validateFloatSanity(float inputValue)
{
    // Step 1: Range check – return early if out of [min, max)
    if ((inputValue < g_minFloatRange) || (g_maxFloatRange <= inputValue))
    {
        return;
    }

    // Step 2: Reinterpret float bits as integer, apply mask, cast back to float
    float maskedValue = (float)((uint32_t)inputValue & g_floatBitMask);

    // Step 3: Verify that masked value equals the expected constant
    if (maskedValue != g_expectedValue)
    {
        handleFloatAssertion();
    }

    // Step 4: Verify that (masked * multiplier) equals the expected constant
    if (maskedValue * g_validationMultiplier != g_expectedValue)
    {
        handleFloatAssertion();
        return;
    }

    return;
}