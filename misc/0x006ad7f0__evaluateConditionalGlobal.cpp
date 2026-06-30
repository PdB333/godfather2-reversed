// FUNC_NAME: evaluateConditionalGlobal

// Function at 0x006ad7f0: Conditional global evaluation.
// If the first parameter (flag) is non-zero, it calls a function on a global pointer
// and returns its result; otherwise returns 0.
// This is a common pattern in EARS engine for checking a condition and delegating
// to a global manager method.

int evaluateConditionalGlobal(int flag)
{
    if (flag != 0) {
        // DAT_01130fa0 is a global pointer, likely to a GameManager or StateManager singleton
        int result = FUN_0043b870(DAT_01130fa0);
        return result;
    }
    return 0;
}