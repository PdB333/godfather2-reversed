// FUNC_NAME: Entity::getScaledValue

float Entity::getScaledValue() {
    // Base value at +0x358 (e.g., damage, health, or other scalar)
    float baseValue = *(float *)(this + 0x358);

    // Retrieve global difficulty/settings manager (singleton)
    void *difficultyMgr = GetDifficultyManager();
    if (difficultyMgr != nullptr) {
        // Type (difficulty level) at +0x2DC
        int type = *(int *)(this + 0x2DC);

        switch (type) {
            case 1:
                // Multiplier at +0x1DF4 (e.g., Easy)
                return baseValue * *(float *)((uintptr_t)difficultyMgr + 0x1DF4);
            case 2:
            case 3:
                // Multiplier at +0x1DFC (Normal / Hard)
                return baseValue * *(float *)((uintptr_t)difficultyMgr + 0x1DFC);
            case 4:
                // Multiplier at +0x1E04 (Very Hard)
                return baseValue * *(float *)((uintptr_t)difficultyMgr + 0x1E04);
        }
    }

    return baseValue;
}