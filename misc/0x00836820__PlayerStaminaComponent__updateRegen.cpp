// FUNC_NAME: PlayerStaminaComponent::updateRegen
// Function address: 0x00836820
// Role: Regenerates or drains a stamina-like value based on current vs. max and a target threshold, with global multipliers.
class PlayerStaminaComponent {
public:
    void updateRegen() {
        // Clear flag bit 0 (indicates update is in progress or needs refresh)
        m_flags &= 0xFFFE;

        if (m_enabled != 0) {
            float current = m_currentValue;
            float maxVal = m_maxValue;

            if (current <= maxVal) {
                // Regen: compute new current from ratio and scale up toward max
                // s_regenMultiplier is usually around 1.0 (global DAT_00e445ac)
                m_targetValue = maxVal * s_regenMultiplier;
                m_currentValue = (s_regenMultiplier - current / maxVal) * maxVal;
            }
            else if (maxVal < (m_targetValue - current)) {
                // Drain exceeded threshold: set target and current using drain multiplier
                // s_drainMultiplier (global DAT_00d5eee4) is likely less than s_regenMultiplier
                m_targetValue = maxVal * s_regenMultiplier;
                m_currentValue = maxVal * s_drainMultiplier;
            }
        }
    }

private:
    // Offsets (relative to this):
    // +0x84: unsigned short flags (bit0 = "update needed")
    unsigned short m_flags;
    // +0xD8: enable flag (non-zero = system is active)
    int m_enabled;
    // +0xAC: maximum value (cap for regen/drain)
    float m_maxValue;
    // +0xB0: target value (intermediate goal)
    float m_targetValue;
    // +0xB4: current value (actual stamina)
    float m_currentValue;

    // Global constants (likely from config or tuning)
    static float s_regenMultiplier; // DAT_00e445ac
    static float s_drainMultiplier; // DAT_00d5eee4
};