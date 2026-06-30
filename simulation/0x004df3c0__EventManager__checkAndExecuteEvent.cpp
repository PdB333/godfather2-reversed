// FUNC_NAME: EventManager::checkAndExecuteEvent
int* EventManager::checkAndExecuteEvent(int* outResult, int* conditionKey, int arg1, int arg2, int arg3)
{
    // Check if the first 16 bytes (4 ints) of the condition key are not all zero
    // conditionKey is likely a GUID or hash representing an event condition
    if ((conditionKey[0] != 0 || conditionKey[1] != 0) ||
        (conditionKey[2] != 0 || conditionKey[3] != 0))
    {
        // Get the singleton EventManager instance
        int* manager = (int*)EventManager::getInstance();
        if (manager != nullptr && *manager != 0)
        {
            // Execute the event action via the manager's internal handler
            EventManager::executeAction(*manager, arg1, arg2, arg3);
            return outResult; // Return unchanged output pointer
        }
    }
    *outResult = 0; // Failed or condition not met
    return outResult;
}