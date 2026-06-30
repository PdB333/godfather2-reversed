// FUNC_NAME: Player::canInteractWithEntity
bool __thiscall Player::canInteractWithEntity(Entity* entity) {
    // Check entity availability flags
    // entity->flags0x249C bit27 (0x8000000) - maybe "isAvailable" or "isAlive"
    // entity->byte0x24A0 bit0 - maybe "isBeingInteractedWith"
    if (((byte)((uint)entity->field_0x249C >> 0x1b) & 1) == 0) {
        // Entity is not flagged as busy/blocked
        if (((*(byte*)(&entity->field_0x24A0) & 1) == 0) &&
            // Virtual function at vtable+0x28c (index 0xA3) - likely entity->isAlive()
            (entity->isAlive())) {
            return true;
        }

        // Check player state for interactive capability
        // player->state0x1F58 bit30 - "isInVehicle"
        // player->state0x1F5C bit7  - "isExitingVehicle"
        // player->state0x1F56 bit0  - "isInCover" or "isCrouching"
        // player->currentTarget (0x2134) - pointer to current interactable object
        if (((((byte)(player->field_0x1F58 >> 30) & 1) == 0) ||
             ((player->field_0x1F5C >> 7) & 1) != 0) ||
            ((*(byte*)&player->field_0x1F56) & 1) != 0 ||
            (player->currentTarget == 0)) {
            return true;
        }
    }
    return false; // Action not possible
}