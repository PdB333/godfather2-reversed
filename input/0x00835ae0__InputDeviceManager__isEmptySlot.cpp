// FUNC_NAME: InputDeviceManager::isEmptySlot
// Function address: 0x00835ae0
// Role: Returns true if the controller slot at the given index is unoccupied.
bool InputDeviceManager::isEmptySlot(uint slotIndex) {
    // Checks the slot state; returns 0 (empty) or non-zero (occupied)
    char slotState = getSlotOccupiedFlag(slotIndex);
    return slotState == '\0';
}