// FUNC_NAME: Entity::registerWithManager
void Entity::registerWithManager() {
    // Get singleton PlayerManager (FUN_009c8f80)
    PlayerManager* mgr = PlayerManager::getInstance();

    // Controller slot configuration struct defined in memory as:
    // +0x00 slotIndex = 2 (player slot 2)
    // +0x04 maxSlots  = 16 (total controller slots)
    // +0x08 flags     = 0
    ControllerSlotConfig config;
    config.slotIndex = 2;
    config.maxSlots  = 16;
    config.flags     = 0;

    // Call the first virtual method of PlayerManager (registerPlayer)
    mgr->registerPlayer(this, &config);
}