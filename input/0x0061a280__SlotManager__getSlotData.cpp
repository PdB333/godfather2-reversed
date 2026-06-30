// FUNC_NAME: SlotManager::getSlotData
// Address: 0x0061a280
// Role: Retrieves a slot data pointer from a global array based on an index obtained from context.
// The array is at 0x011a0f38, each element is 0x38 bytes.
// The function first attempts to get an index from FUN_00611000(). If that fails (0xffffffff),
// it tries FUN_00606b50(). If that also fails, returns 0.
// Then validates via FUN_00610e20() (likely a boolean check), and performs bounds and sentinel checks.
// Sentinel offset -0x11a0f28 (0xFEE5F0D8 as unsigned) probably marks an invalid entry.
// Returns pointer to slot data, or 0 if invalid.

void* SlotManager::getSlotData() {
    uint slotIndex;
    
    slotIndex = getPrimaryIndex();      // FUN_00611000
    if (slotIndex == 0) {
        return 0;
    }
    if (slotIndex == 0xffffffff) {
        slotIndex = getFallbackIndex(); // FUN_00606b50
        if (slotIndex == 0xffffffff) {
            return 0;
        }
        if (isSlotValid() == false) {   // FUN_00610e20
            return 0;
        }
    }
    // Bounds check and sentinel offset check
    if ((slotIndex < 0x1000) && (slotIndex * 0x38 != -0x11a0f28)) {
        return (void*)(&gSlotArray + slotIndex * 0x38); // DAT_011a0f38
    }
    return 0;
}