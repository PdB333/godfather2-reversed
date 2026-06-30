// FUNC_NAME: HandleManager::resolveHandle
uint HandleManager::resolveHandle(uint handle, void* param) {
    // Table of entries, each 0x30 bytes, starting at offset 0x10 from global base
    // Max 512 entries (0x200)
    uint result = in_EAX & 0xffffff00; // Preserve upper bits from EAX (likely return value from caller)
    uint index = handle & 0xffff;
    if (index < 0x200) {
        uint* entry = (uint*)(DAT_012234bc + 0x10 + index * 0x30);
        if (entry != nullptr && entry[0x2c / 4] == handle) { // +0x2c stores the handle for validation
            result = FUN_005e5fe0(param); // Call internal function with param
        }
    }
    return result;
}