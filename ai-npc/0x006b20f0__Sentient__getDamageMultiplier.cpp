// FUNC_NAME: Sentient::getDamageMultiplier
// Function address: 0x006b20f0
// Returns a damage multiplier based on stat index and current state/health.
// Offsets: this+0x40 = pointer to health component, this+0x16c = state enum (2,3,4 = damage states)
// Global table at DAT_00e50d14: array of floats, each entry 16 bytes.

float __thiscall Sentient::getDamageMultiplier(int thisPtr, float statIndex)
{
    int state;
    float healthFactor;
    float baseMultiplier;

    // Look up base multiplier from global table indexed by statIndex (each entry 16 bytes)
    baseMultiplier = *(float*)((char*)&g_statTable + (int)statIndex * 0x10);

    // Get health factor from health component at offset +0x40
    healthFactor = (float)getHealthFactor(*(int*)(thisPtr + 0x40)); // FUN_008c7710

    // If healthFactor > 0 and state is one of the damage states (2,3,4), multiply
    if ((healthFactor > 0.0f) &&
        ((state = *(int*)(thisPtr + 0x16c), state == 2 || state == 3 || state == 4)))
    {
        baseMultiplier = healthFactor * baseMultiplier;
    }

    return baseMultiplier;
}