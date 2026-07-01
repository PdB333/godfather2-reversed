// FUNC_NAME: ControllerManager::updatePriorityInput

void ControllerManager::updatePriorityInput(void)
{
    int result = 0;

    // Check primary controller source (e.g., player entity)
    if ((g_PlayerEntity != NULL) && (*(int *)(g_PlayerEntity + 0xd8) != NULL)) {
        result = tryAcquireInputPriority(2); // Highest priority (e.g., gameplay)
    }

    // Check secondary input source (e.g., UI camera or cutscene)
    if ((g_UIHandler != NULL) && 
        ((*(int *)(g_UIHandler + 100) < 8 || (19 < *(int *)(g_UIHandler + 100))))) {
        // Only activate if the first priority wasn't claimed
        if (result != 0) {
            return;
        }
        result = tryAcquireInputPriority(1); // Medium priority (e.g., UI)
    }

    // Default to lowest priority if nothing claimed
    if (result == 0) {
        tryAcquireInputPriority(0); // Idle/background input
    }
    return;
}