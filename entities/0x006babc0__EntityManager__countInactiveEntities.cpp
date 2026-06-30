// FUNC_NAME: EntityManager::countInactiveEntities
// Address: 0x006babc0
// This function counts entities in a list that are considered inactive, dead, or destroyed.
// The list is stored as a pointer to an array of entity pointers at offset 0x00,
// and the count at offset 0x04.
// It checks multiple flags and component states to determine inactivity.

int EntityManager::countInactiveEntities(int* this) {
    uint index = 0;
    int inactiveCount = 0;

    // If the list is non-empty
    if (this[1] != 0) {
        int** entityArray = (int**)(this[0]); // pointer to array of entity pointers
        do {
            int* entity = entityArray[index]; // entity pointer
            // Check if the entity is pending destruction through global death check
            bool isDead = (FUN_007912e0() != 0); // possibly IsEntityPendingDeath()
            if (!isDead) {
                // Read flags at offset 0x5C (common entity state flags)
                uint flags = *(uint*)(entity + 0x5C / 4); // offset 0x5C
                // Check for bits: 0x60000 (destroyed/pending delete), 0x100000 (removed), 0x4000000 (hidden)
                if ((flags & 0x60000) == 0 &&
                    (flags & 0x100000) == 0 &&
                    (flags & 0x4000000) == 0) {
                    // Additionally, check a component's health/death state
                    int* healthComponent = FUN_00791540(); // returns a component pointer (e.g., HealthComponent)
                    if (healthComponent != nullptr) {
                        // Read byte at offset 0x84, check bit 5 (dead flag)
                        uint healthFlags = *(uint*)(healthComponent + 0x84 / 4);
                        if ((~(healthFlags >> 5) & 1) == 0) {
                            // bit5 is set -> entity is dead
                            isDead = true;
                        }
                    }
                } else {
                    // Some destruction flags set -> entity is inactive
                    isDead = true;
                }
            }
            if (isDead) {
                inactiveCount++;
            }
            index++;
        } while (index < (uint)this[1]);
    }
    return inactiveCount;
}