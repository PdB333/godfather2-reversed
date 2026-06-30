// FUNC_NAME: SomeManager::accessTableEntry
// Address: 0x0061a280
// Role: Retrieves a 32-bit value from a global table indexed by a validated handle.
// Calls: FUN_00611000 (getPrimaryHandle?), FUN_00606b50 (getSecondaryHandle?), FUN_00610e20 (isHandleValid?)
// Global array: gEntryTable at 0x011a0f38, element size 0x38 bytes.

uint32_t SomeManager::accessTableEntry() {
    uint32_t handle = getPrimaryHandle(); // FUN_00611000
    if (handle == 0) {
        return 0;
    }
    if (handle == 0xFFFFFFFF) { // -1 indicates invalid primary
        handle = getSecondaryHandle(); // FUN_00606b50
        if (handle == 0xFFFFFFFF) {
            return 0;
        }
        bool valid = isHandleValid(handle); // FUN_00610e20
        if (!valid) {
            return 0;
        }
    }
    // Bounds check: handle must be less than 0x1000 (max array size)
    // Additionally, ensure the offset is not a sentinel value -0x11a0f28 (likely a null/zero check misdecoded)
    if ((handle < 0x1000) && (handle * 0x38 != 0xFEE5F0D8)) { // -0x11a0f28 = 0xFEE5F0D8, likely check against 0
        return *(uint32_t*)(&gEntryTable + handle * 0x38);
    }
    return 0;
}