// FUNC_NAME: Sentient::tryTriggerAction
// Function at 0x007696e0: Checks if a random probability test passes and an inner condition is met, based on current state.
// This appears to be an AI decision-making helper.

class Sentient {
public:
    int field_0x74; // +0x74: State/enum field; 0 = invalid, 0x48 = disabled
    // ... other members
};

// Constants from global data
static const float g_invRandMax = DAT_00e44590; // Likely 1.0f / RAND_MAX
static const float g_randOffset  = DAT_00e51bc0; // Likely 0.0f

bool Sentient::tryTriggerAction(float probability) {
    // Only allow if state is valid and not disabled
    if (field_0x74 != 0 && field_0x74 != 0x48) {
        // Generate random float in [0, 1)
        float randFloat = (float)rand() * g_invRandMax + g_randOffset;
        if (randFloat < probability) {
            // Call additional check (likely another virtual/global function)
            if (FUN_007695b0()) { // This may be a global or member function
                return true;
            }
        }
    }
    return false;
}