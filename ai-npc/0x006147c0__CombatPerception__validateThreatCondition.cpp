// FUNC_NAME: CombatPerception::validateThreatCondition
void __fastcall validateThreatCondition(int entityIndex)
{
    float vec[3];   // local_20 - position or direction from entity
    float w;        // fStack_14 - fourth component (e.g. distance squared or weight)

    // Fetch entity data (e.g., position, distance) from global manager
    FUN_0056b480(&DAT_011f6af0, entityIndex, vec);
    w = *(float*)&vec[3]; // fourth element from call (compiler allocated after array)

    if (w <= 0.0f)
        return;

    // Random factor from EDX low 16 bits (likely RNG seed)
    float randomFactor = (float)(extraout_EDX & 0xFFFF);

    // Global constants used in threat calculation
    float k1 = DAT_00e2b1a4; // some distance/scale factor
    float k2 = DAT_00e2cd54; // sensitivity multiplier
    float k3 = DAT_00e44564 - _DAT_011f6a30; // delta from two globals
    float invW = k1 / w;

    // Compute combined condition using position x, random, global constants, and incoming float (XMM7)
    float term1 = (invW * vec[0] + k1) * randomFactor * k2;
    float term2 = k3 * randomFactor * k2 * invW * in_XMM7_Da;

    if (term1 + term2 < 0.0f)
        return;
    // If both checks pass, function falls through (action presumably handled by caller)
}