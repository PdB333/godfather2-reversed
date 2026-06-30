// FUNC_NAME: validateAndExecuteAction

uint validateAndExecuteAction(uint param_1)
{
    uint adjusted = calculateValue(param_1);
    if (adjusted < 0x14) {
        adjustValue(&adjusted);
        executeAction();
        return 1;
    }
    return 0;
}