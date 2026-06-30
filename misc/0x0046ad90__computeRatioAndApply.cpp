// FUNC_NAME: computeRatioAndApply
// Address: 0x0046ad90
// Role: Computes a ratio from two values (likely resource counters) and applies it to a context object.
// Calls getValue(1) and getValue(2) via FUN_0046ab80, then sets scaled value via applyRatio.
// Throws division-by-zero error via debug break if denominator is zero.

void computeRatioAndApply(undefined4 context) // context is likely a pointer to an object (e.g., a manager)
{
    uint numerator = getValue(1);   // FUN_0046ab80(1) - gets first value (e.g., current)
    uint denominator = getValue(2); // FUN_0046ab80(2) - gets second value (e.g., max)

    if (denominator != 0) {
        applyRatio(context, numerator / denominator); // FUN_0046aac0 - sets scaled value in context
        return;
    }

    // Division by zero error
    FUN_00627bd0("UInt32 operator / : Tried to divide by zero.");
    // Debug breakpoint
    __debugbreak();
}