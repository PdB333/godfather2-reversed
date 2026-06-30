// FUNC_NAME: PlayerManager::updatePlayerSlot
// Function address: 0x006b0f90
// Role: Checks if a player slot is active, then updates the player state

void PlayerManager::updatePlayerSlot(int slotIndex, PlayerData* player) {
    bool isActive = this->isSlotActive(slotIndex); // calls FUN_006b0ee0
    if (isActive) {
        this->updatePlayer(player); // calls FUN_006b4fc0
    }
}