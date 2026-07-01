// FUNC_NAME: DecisionMaker::evaluateChance
// Address: 0x008bd720
// Role: Probability threshold test with optional delegation.
// Offsets: this+0xfc = flag to bypass logic and call delegate.

extern float g_veryLowThreshold;   // _DAT_00d5efd0
extern float g_midLowThreshold;    // _DAT_00d577a0
extern float g_highThreshold;      // _DAT_00d5780c

// Delegate function at 0x006b18a0
int __fastcall delegateRandomCheck();

int __thiscall DecisionMaker::evaluateChance(float param_2)
{
    // param_2 is the second float parameter.
    // The first float parameter (from XMM0) is used as multiplier.
    float local_8;
    param_2 = in_XMM0 * param_2;  // Multiply the two input factors.

    // If the bypass flag is set, delegate to a random check.
    if (*(int*)(this + 0xfc) != 0) {
        return delegateRandomCheck();
    }

    if (g_highThreshold <= param_2) {
        // High range: return the rounded value of param_2.
        local_8 = (float)(int)(param_2 + 0.5f); // ROUND
        return (int)local_8;
    }

    if ((g_veryLowThreshold < param_2) && (param_2 < g_highThreshold)) {
        // Medium range: return 1.
        return 1;
    }

    // Low range: return 0.
    return 0;
}