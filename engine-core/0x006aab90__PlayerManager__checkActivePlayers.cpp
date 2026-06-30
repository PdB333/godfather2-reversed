// FUNC_NAME: PlayerManager::checkActivePlayers
void PlayerManager::checkActivePlayers() {
    bool anyActive = false;
    uint count = *(uint *)(this + 0x360); // Number of player slots

    if (count != 0) {
        int *slotBase = (int *)(this + 8); // Base of player slot array (each slot 108 bytes)
        for (uint i = 0; i < count; i++) {
            // Check if slot is occupied: fields at offsets 0, 0x10, 0x5C within slot
            if (slotBase[0x17] != 0 && *slotBase != 0 && slotBase[4] != 0) {
                // Call a function on the manager (this) to validate the slot
                if (FUN_006aa5e0(this)) {
                    anyActive = true;
                }
            }
            slotBase += 0x1b; // Advance to next slot (27 ints = 108 bytes)
        }
        if (anyActive) {
            FUN_006aaa20(); // Global update/notification
        }
    }
}