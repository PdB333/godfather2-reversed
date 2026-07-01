//FUNC_NAME: SlotManager::findSlotByID
int __thiscall SlotManager::findSlotByID(int thisPtr, int id) {
    // Returns index of slot with matching ID, or -1 if not found.
    // Slots are stored at offset +0x18, each 36 bytes (0x24).
    // Bit 1 of flags indicates slot is active.
    if (id == 0) {
        return -1;
    }

    SlotEntry* slots = reinterpret_cast<SlotEntry*>(thisPtr + 0x18);
    for (int i = 0; i < 7; i++) {
        SlotEntry* entry = &slots[i];
        // Check if slot is active (bit 1 set)
        if ((entry->flags >> 1) & 1) {
            if (entry->getID() == id) {
                return i;
            }
        }
    }
    return -1;
}