// FUNC_NAME: Sentient::shouldTriggerRandomAction
bool __thiscall Sentient::shouldTriggerRandomAction(float probabilityThreshold) {
    // Global probability curve parameters (probably from AI data tables)
    float probabilityBase = s_ProbabilityBase;   // DAT_00e51bbc - base offset for random roll
    float probabilityScale = s_ProbabilityScale; // DAT_00e44590 - scaling factor for rand

    // +0x74: AI state/behavior flag (0 = idle, 0x48 = some specific blocking state)
    int aiState = *(int*)(this + 0x74);

    // Only attempt random action if not idle and not in the blocked state
    if (aiState != 0 && aiState != 0x48) {
        int r = rand();
        float roll = (float)r * probabilityScale + probabilityBase;
        if (roll < probabilityThreshold) {
            // Delegate to the actual behavior execution
            if (performAction()) {
                return true;
            }
        }
    }
    return false;
}