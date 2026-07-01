// FUNC_NAME: SlotManager::updateSlotAssignment
void __thiscall SlotManager::updateSlotAssignment(SlotEntry* entry) {
    byte oldSlotIndex = entry->slotIndex; // +0x12
    byte newSlotIndex = getSlotIndexFromItemId(entry->itemId); // FUN_007ee560

    if (newSlotIndex != oldSlotIndex) {
        this->slotCounts[oldSlotIndex]--; // array at +0x14
        this->slotCounts[newSlotIndex]++;
        entry->slotIndex = newSlotIndex;
    }
}