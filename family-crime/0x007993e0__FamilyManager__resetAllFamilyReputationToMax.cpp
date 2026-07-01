// FUNC_NAME: FamilyManager::resetAllFamilyReputationToMax

// Function at 0x007993e0: Resets all family reputations to maximum (99999) and clears additional stats.
// Called when starting a new campaign or reloading state.

void __thiscall FamilyManager::resetAllFamilyReputationToMax(FamilyManager *this)
{
    // Virtual function at vtable+0x254: checks if the campaign/game is active
    bool isActive = (*(bool (__thiscall **)(FamilyManager *))(*(int *)this + 0x254))(this);
    
    if (isActive) {
        // Loop through all 6 family slots (0-5)
        for (int familyIdx = 0; familyIdx < 6; familyIdx++) {
            // Get current reputation for this family (addr 0x00700090)
            uint currentRep = getFamilyReputation(familyIdx);
            // If below max (99999), set to max (addr 0x007000a0)
            if (currentRep < 99999) {
                setFamilyReputation(familyIdx, 99999);
            }
        }
    }

    // Reset additional statistics for indices 6,7,8 (likely notoriety, fear, etc.)
    // addr 0x00706380: generic stat reset function
    resetFamilyStatistic(6);
    resetFamilyStatistic(7);
    resetFamilyStatistic(8);
}