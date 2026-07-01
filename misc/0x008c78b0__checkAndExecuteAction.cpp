// FUNC_NAME: checkAndExecuteAction
// Function address: 0x008c78b0
// Role: Conditional check and action execution. Checks a condition on param_1 (likely an object or state) and if true, performs an action on param_2 (likely data or another object).
void checkAndExecuteAction(void* obj, void* actionData)
{
    int conditionResult;

    conditionResult = isConditionMet(obj); // FUN_008c74d0 - checks some condition (e.g., object validity, state flag)
    if (conditionResult != 0) {
        performAction(actionData); // FUN_008be4e0 - executes the action (e.g., play animation, start mission)
    }
    return;
}