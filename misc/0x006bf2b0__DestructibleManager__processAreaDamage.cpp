// FUNC_NAME: DestructibleManager::processAreaDamage
// Address: 0x006bf2b0
// Manages area damage to a list of entities, applying damage if game state > 2

void DestructibleManager::processAreaDamage()
{
    // Get the internal object containing entity list and transform data
    int* object = *(int**)(this + 0x10);   // this->pObject at +0x10

    // Copy from local transform buffer (this+0x28) to object's world transform buffer (object+0xa8)
    // Size comes from a value stored in another object (this+0x18) at offset 0x54
    FUN_006beed0(object + 0xa8, this + 0x28,
                 *(int*)(*(int*)(this + 0x18) + 0x54));

    int damageType = *(int*)(object + 0x38);  // +0x38: type/severity of damage
    uint entityCount = *(uint*)(object + 0xa0); // +0xa0: number of entities in list

    // Iterate over entity list if it exists
    if (entityCount != 0) {
        for (uint i = 0; i < entityCount; i++) {
            // Get entity pointer from array at object+0x9c
            int entity = *(int*)(*(int*)(object + 0x9c) + i * 4);
            // Check global game state (difficulty/level)
            int gameState = FUN_00791750();
            if (gameState > 2) {
                // Apply damage to entity: entity, reason 2, severity, flag 0
                FUN_008bf280(entity, 2, damageType, 0);
            }
        }
    }

    // Copy from local transform buffer back to the entity list pointer location (object+0x9c)
    FUN_006beed0((int*)(object + 0x9c), this + 0x28,
                 *(int*)(*(int*)(this + 0x18) + 0x54));
}