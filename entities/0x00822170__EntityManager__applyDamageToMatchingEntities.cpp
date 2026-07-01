// FUNC_NAME: EntityManager::applyDamageToMatchingEntities
void __thiscall EntityManager::applyDamageToMatchingEntities(int thisPtr, int* damageDataPtr)
{
    float baseValue = DAT_00d5780c;  // global base damage value

    // Compute the adjustment to apply to the parent entity
    float parentAdjustment = 0.0f;
    int subEntityValue = 0;
    if (damageDataPtr != nullptr) {
        // damageDataPtr[0] is a pointer to a target entity, damageDataPtr[1] is a float (damage value)
        float targetDamage = *(float*)(damageDataPtr + 1);
        parentAdjustment = baseValue - targetDamage - baseValue; // equals -targetDamage
        subEntityValue = targetDamage;
    }

    // Number of entities in this manager's list
    uint entityCount = *(uint*)(thisPtr + 0x3c);
    int entityArrayBase = *(int*)(thisPtr + 0x24);

    for (uint i = 0; i < entityCount; i++) {
        int currentEntity = entityArrayBase + i * 0x130;
        // Check if entity is active (ID != 0)
        if (*(int*)(currentEntity + 0xb0) != 0) {
            bool parentProcessed = false;

            if (damageDataPtr != nullptr) {
                int* targetEntity = (int*)*damageDataPtr; // damageDataPtr[0]
                // Compare owner ID: target +0xc vs this +0xc
                if (*(int*)(targetEntity + 0xc) == *(int*)(thisPtr + 0xc)) {
                    uint subEntityCount = *(uint*)(targetEntity + 0x28); // +0x28
                    int subArrayBase = *(int*)(targetEntity + 0x24); // +0x24

                    for (uint j = 0; j < subEntityCount; j++) {
                        int currentSub = subArrayBase + j * 0x130;
                        // Compare sub-entity ID with current entity ID
                        if (*(int*)(currentSub + 0xb0) == *(int*)(currentEntity + 0xb0)) {
                            if (!parentProcessed) {
                                // Apply negative adjustment to the parent entity
                                FUN_00820520(currentEntity, parentAdjustment);
                                parentProcessed = true;
                            }
                            // Apply positive damage value to the sub-entity
                            FUN_00820520(currentSub, subEntityValue);
                        }
                    }
                }
            }
            // Post-processing for this entity
            FUN_00820ae0();
        }
    }
}