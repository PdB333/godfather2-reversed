// FUNC_NAME: Player::updateDirectionalValue

// Function at 0x007f4f20: Updates a mapped integer value based on a float and direction flag.
// Fields:
//   this+0x6d0: float mCurrentFloat
//   this+0x6dc: byte mFlags (bit 3 = directionFlag)
//   this+0x6c4: int mMappedInt
// Global thresholds: g_lowerThreshold (likely 0.0), g_upperThreshold (likely 1.0)
// Global multiplier: g_rangeMultiplier

void __thiscall Player::updateDirectionalValue(int this, bool increaseDirection) {
    float currentFloat = *(float *)(this + 0x6d0);
    
    if (!increaseDirection) {
        // Decreasing direction
        if (currentFloat < g_lowerThreshold) {
            // Only update if direction flag is set or mapped int is 0
            if (((*(byte *)(this + 0x6dc) & 8) != 0) || (*(int *)(this + 0x6c4) == 0)) {
                *(int *)(this + 0x6c4) = (int)(currentFloat * g_rangeMultiplier + g_lowerThreshold);
            }
            // Clear direction flag (bit 3)
            *(byte *)(this + 0x6dc) = *(byte *)(this + 0x6dc) & 0xf7;
        }
    } else {
        // Increasing direction
        if (currentFloat > g_upperThreshold) {
            // Only update if direction flag is clear or mapped int is 0
            if ((*(byte *)(this + 0x6dc) & 8) == 0 || (*(int *)(this + 0x6c4) == 0)) {
                *(int *)(this + 0x6c4) = (int)((1.0f - currentFloat) * g_rangeMultiplier + 1.0f);
            }
            // Set direction flag (bit 3)
            *(byte *)(this + 0x6dc) = *(byte *)(this + 0x6dc) | 8;
        }
    }
}