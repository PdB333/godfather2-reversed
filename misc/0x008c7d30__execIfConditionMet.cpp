// FUNC_NAME: execIfConditionMet
void execIfConditionMet(void* thisPtr, void* param2)
{
    int conditionResult = checkCondition(thisPtr);
    if (conditionResult != 0) {
        performAction(param2);
    }
    return;
}