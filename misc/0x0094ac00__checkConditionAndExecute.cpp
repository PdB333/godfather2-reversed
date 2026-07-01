// FUNC_NAME: checkConditionAndExecute
// Function address: 0x0094ac00
// Role: Checks a condition on an object handle (via pointer), and if valid (result >= 0), executes a secondary action with three parameters.
// Likely used for safe execution of commands that require a valid target.

void __cdecl checkConditionAndExecute(int objectHandle, int actionParam1, int actionParam2, int actionParam3)
{
    // FUN_00949380: Validates/retrieves state associated with objectHandle; returns >=0 if valid.
    int validationResult = FUN_00949380(&objectHandle); // Takes address of objectHandle (stack copy)
    if (validationResult >= 0) {
        // FUN_0094a020: Performs the actual action (e.g., apply effect, start animation, etc.)
        FUN_0094a020(actionParam1, actionParam2, actionParam3);
    }
}