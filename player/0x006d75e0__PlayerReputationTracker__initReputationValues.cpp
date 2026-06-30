// FUNC_NAME: PlayerReputationTracker::initReputationValues
void __thiscall PlayerReputationTracker::initReputationValues(void* param_2)
{
    // Copy or process data from param_2 (likely a reputation structure)
    FUN_006bfa70(param_2); // Inline: unknown helper, possibly memcpy or parse

    // Set flag indicating initialization completed
    *(byte*)(this + 0x248) = 1;

    // Compare current reputation value (float at +0x240) against global threshold
    float currentRep = *(float*)(this + 0x240);
    float threshold = _DAT_00d5780c; // Global threshold constant
    float factor = _DAT_00d5f51c;    // Global scaling factor
    int baseValue = DAT_01205224;    // Global base integer (e.g., max reputation)

    if (currentRep <= threshold)
    {
        // Clamp to base value if current reputation is low
        *(int*)(this + 0x23c) = baseValue;
    }
    else
    {
        // Scale down the base value by current reputation times factor
        int scaledReduction = (int)(longlong)ROUND(currentRep * factor);
        *(int*)(this + 0x23c) = baseValue - scaledReduction;
    }

    // Zero out additional fields
    *(int*)(this + 0x258) = 0; // +0x258 (offset 600 decimal)
    *(int*)(this + 0x25c) = 0; // +0x25c
}