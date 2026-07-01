// FUNC_NAME: Entity::isAlive
bool __thiscall Entity::isAlive(void) {
    // +0x54: typeId (magic constant 0x637b907)
    // +0x84: flags (bit 3 = alive flag)
    // Global pointer DAT_0112aa1c likely to GameManager
    // +0x2c6c: globalFlags (bit 7 = some gameplay state, e.g., cutscene)
    // +0x2c88: pointer to something (e.g., player controller) that might override

    bool alive = false;

    if (this != 0) {
        // Read the "alive" bit from flags at +0x84 bit 3
        alive = (*(uint32 *)((char *)this + 0x84) >> 3 & 1) != 0;

        // Check if this entity is of the specific type (e.g., sentient or player)
        if (*(int *)((char *)this + 0x54) == 0x637b907) {
            // Check global game state that forces entity to be considered dead/inactive
            uint32 globalFlags = *(uint32 *)(DAT_0112aa1c + 0x2c6c);
            int *globalOverridePtr = *(int **)(DAT_0112aa1c + 0x2c88);

            if ((globalFlags & (1 << 7)) != 0 ||
                (globalOverridePtr != 0 && FUN_00784770() != 0)) {
                // Game is in a state where this entity should not be considered alive
                return false;
            }
        }
    }
    return alive;
}