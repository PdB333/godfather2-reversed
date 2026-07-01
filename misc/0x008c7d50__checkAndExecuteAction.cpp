// FUNC_NAME: checkAndExecuteAction
void checkAndExecuteAction(void* object, uint actionData) {
    // Check if the object allows the action (e.g., is idle, has resources, etc.)
    if (isActionAllowed(object)) {
        // Execute the action using the provided data
        executeAction(actionData);
    }
}