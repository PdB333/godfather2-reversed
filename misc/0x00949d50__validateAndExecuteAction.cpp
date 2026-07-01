// FUNC_NAME: validateAndExecuteAction
void validateAndExecuteAction(void* context, int actionType, int targetId, int extraData)
{
    int validationResult = validateAction(context);
    if (validationResult >= 0) {
        executeAction(actionType, targetId, extraData);
    }
}