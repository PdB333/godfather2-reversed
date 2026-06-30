// FUNC_NAME: GameManager::isAnySlotActive
// Function address: 0x00690e60
// Role: Checks if any of the four slots (e.g., player slots) is active by iterating through slot data.
// Calls FUN_004973e0 to get a pointer to slot data array, then checks each slot via FUN_0049a870 and FUN_00b930b0.
int __thiscall GameManager::isAnySlotActive(void* thisPtr) {
    // Get pointer to slot data array (first two elements are handles)
    uint* slotData = (uint*)FUN_004973e0(thisPtr);
    if (slotData != nullptr) {
        uint handle1 = slotData[0]; // +0x00: first handle
        uint handle2 = slotData[1]; // +0x04: second handle
        // Check up to 4 slots (indices 0-3)
        for (uint slotIndex = 0; slotIndex < 4; slotIndex++) {
            char slotByte = FUN_0049a870(handle1, handle2, slotIndex);
            char isActive = FUN_00b930b0(slotByte);
            if (isActive != '\0') {
                return 1; // At least one slot is active
            }
        }
    }
    return 0; // No active slots
}