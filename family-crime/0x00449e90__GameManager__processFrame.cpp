// FUNC_NAME: GameManager::processFrame
void __thiscall GameManager::processFrame(GameManager* this)
{
    // Call virtual method at vtable offset 8 (likely onUpdate/tick)
    (**(code **)(this[0] + 8))();

    // Global pointer to an objective or event object (e.g., mission objective)
    if (g_pMissionObjective != 0) {
        // Check if the objective is still active (returns 0 if completed/inactive)
        char isActive = isObjectiveActive(g_pMissionObjective);
        if (isActive == '\0') {
            // Increment global counter (e.g., completed objectives count)
            g_missionCompleteCount = g_missionCompleteCount + 1;
            // Finalize the objective with flag 0x8000 (e.g., success/completion type)
            finishObjective(g_pMissionObjective, 0x8000);
        }
    }
}