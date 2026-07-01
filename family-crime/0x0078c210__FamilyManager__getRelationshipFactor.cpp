// FUNC_NAME: FamilyManager::getRelationshipFactor
// Address: 0x0078c210
// Returns a relationship multiplier between two family IDs (e.g., 0-neutral, 3-Corleone, 4/5-enemy factions).
// Constants from global data: kFactorFamily3 (0x00d69a74), kFactorEnemy (0x00d69a78), kFactorDefault (0x00d69a7c), kFactorZero (0x00d69a80).

float FamilyManager::getRelationshipFactor(int familyId1, int familyId2)
{
    // Hard-coded constants (likely 1.0, 0.0, etc.)
    if ((familyId1 == 3) || (familyId2 == 3)) {
        return *(float*)0x00d69a74; // e.g., 1.0f
    }
    if ((familyId1 != 0) && (familyId2 != 0)) {
        if ((((familyId1 != 4) && (familyId1 != 5)) && (familyId2 != 4)) && (familyId2 != 5)) {
            return *(float*)0x00d69a7c; // default for non-enemy, non-neutral, non-3 families
        }
        return *(float*)0x00d69a78; // enemy modifier (both are 4 or 5)
    }
    return *(float*)0x00d69a80; // one of the families is neutral (0)
}