// FUNC_NAME: ScriptEventManager::processEvent
// Function address: 0x008af670
// Role: Handles script event triggers based on game state. Increments event counter when scripts are active,
//       or allocates and executes a script action when user interaction is detected.

void __fastcall ScriptEventManager::processEvent()
{
    char scriptActive; // Flag from engine
    int eventIndex; // +0x104: Counter for script events
    int actionData; // Pointer or ID returned by getActionParameter

    // Check if the scripting engine is currently processing
    scriptActive = isScriptEventProcessingEnabled();
    if (scriptActive != '\0') {
        // Increment the event counter and call the event processor with the old index
        eventIndex = *(int *)(this + 0x104);
        *(int *)(this + 0x104) = eventIndex + 1;
        processQueuedEvent(eventIndex);
        return;
    }

    // Check if user interaction (e.g., dialog choice, prompt) is active
    scriptActive = isUserInteractionActive();
    if (scriptActive != '\0') {
        // Allocate a block for action data (size 0x38 corresponds to a structure like ScriptActionParameter)
        actionData = allocateScriptActionData(0x38);
        if (actionData != 0) {
            // Retrieve the current action parameter from the script manager
            actionData = getCurrentActionParameter(this);
            // Execute the script action using the allocated data
            executeScriptAction(actionData);
            return;
        }
        // Allocation failed, execute a null action (perhaps error handling)
        executeScriptAction(0);
    }
    return;
}