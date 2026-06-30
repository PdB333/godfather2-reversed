// FUNC_NAME: checkConditionAndGetResult
unsigned int __thiscall checkConditionAndGetResult(void* this) {
    int conditionResult;
    unsigned int value;

    conditionResult = FUN_006b0ee0(this);
    if (conditionResult != 0) {
        value = FUN_006b6680();
        return value;
    }
    return 0;
}