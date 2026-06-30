// FUNC_NAME: PlayerSlotManager::setSlotIdForPlayer
bool PlayerSlotManager::setSlotIdForPlayer(Player* player, uint32_t slotId) {
    // Validate player pointer
    if (player == nullptr) {
        return false;
    }

    // Array of 5 slot structs at this+0x490, each 0x4A4 bytes
    // Slot struct layout (offsets relative to slot base):
    //   +0x000: Player* owner (4 bytes)
    //   +0x248: uint32_t slotId (4 bytes)
    const int MAX_SLOTS = 5;
    const int SLOT_SIZE = 0x4A4;
    const int SLOT_ARRAY_OFFSET = 0x490;
    const int SLOT_ID_OFFSET = 0x248;

    for (int i = 0; i < MAX_SLOTS; ++i) {
        uint8_t* slot = reinterpret_cast<uint8_t*>(this) + SLOT_ARRAY_OFFSET + i * SLOT_SIZE;
        Player* current = *reinterpret_cast<Player**>(slot);
        if (current == player) {
            // Found matching slot, store the slot ID
            *reinterpret_cast<uint32_t*>(slot + SLOT_ID_OFFSET) = slotId;
            return true;
        }
    }
    return false;
}