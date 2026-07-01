// FUNC_NAME: DamageSystem::calculateModifiedDamage

int DamageSystem::calculateModifiedDamage(void *pTarget, int damageTypeId, int damageCategoryId,
                                           int weaponTypeId, uint baseDamage, int damageMultiplier,
                                           int maxDamage)
{
    uint accumulatedDamage = 0;
    int resultDamage = 0;

    if (pTarget == nullptr) {
        return 0;
    }

    int *hash1 = (int *)GetHashFromId(damageTypeId);          // FUN_004baf60
    int *hash2 = (int *)GetHashFromId(damageCategoryId);      // FUN_004baf60

    // If both hashes are valid and equal, return -1 (immunity/special case)
    if (hash1 != nullptr && hash2 != nullptr && *hash1 == *hash2) {
        return -1;
    }

    if (damageTypeId != -1) {
        // Start iteration over damage modifiers for pTarget with key damageTypeId
        DamageModifierIterator iter;
        StartDamageModifierIteration(&iter, pTarget, damageTypeId);  // FUN_004bab20

        while (iter.hasNext() || iter.currentIsValid()) {
            int modifierData = (*iter.getCurrentFunctionPointer)();   // returns pointer to modifier struct
            int damageModifierType = *(int *)(modifierData + 8);
            int modifierAmount = *(int *)(modifierData + 0xC);
            int modifierSource = *(int *)(modifierData + 0x10);
            int modifierOtherId = *(int *)(modifierData + 0x14);     // used as secondary source

            // Case 1: specific weapon type and source match, positive amount
            if (damageModifierType == weaponTypeId &&
                modifierSource == damageTypeId &&
                modifierAmount > 0) {
                accumulatedDamage += 1;
                (*iter.advanceFunctionPointer)();
            }
            // Case 2: global special damage type (e.g., fall/explosion) with amount > 1 and source matches
            else if (damageModifierType == SPECIAL_DAMAGE_TYPE_0x00e54378 &&
                     modifierAmount > 1 &&
                     modifierSource == damageTypeId) {
                accumulatedDamage = (accumulatedDamage - 2) + (modifierAmount / damageMultiplier) + baseDamage;
                (*iter.advanceFunctionPointer)();
            }
            else {
                // Break if secondary source matches or amount is negative
                if (modifierOtherId == damageTypeId || modifierAmount < 0) {
                    break;
                }
                (*iter.advanceFunctionPointer)();
            }
        }

        if (baseDamage <= accumulatedDamage) {
            resultDamage = ((accumulatedDamage - baseDamage) + 2) * damageMultiplier;
        }
    }

    // Cap result to maxDamage
    if (maxDamage < resultDamage) {
        resultDamage = maxDamage;
    }
    return resultDamage;
}