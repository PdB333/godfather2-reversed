// FUNC_NAME: PlayerCCTVariables::getAdjustedRange
void __thiscall PlayerCCTVariables::getAdjustedRange(float *outMin, float *outMax)
{
    // Read raw min/max from object offsets +0x54 and +0x58
    *outMin = *(float *)(this + 0x54);
    *outMax = *(float *)(this + 0x58);

    // Check global game mode: pointer at g_globalState+4 must be non-null and not 0x1f30
    if ((**(int **)(g_globalState + 4) != 0) && (**(int **)(g_globalState + 4) != 0x1f30))
    {
        float sum = (*outMin + *outMax) * g_smoothingFactor; // _DAT_00d5c458
        float newMin = sum - (*outMax - sum);
        *outMax = (*outMax - sum) + sum; // effectively *outMax = *outMax (no change?)
        *outMin = newMin;

        // Clamp min to 0
        if (*outMin < 0.0f)
            *outMin = 0.0f;

        // Clamp max to global max limit
        if (*outMax > g_maxRange) // DAT_00d5e288
            *outMax = g_maxRange;
    }
}