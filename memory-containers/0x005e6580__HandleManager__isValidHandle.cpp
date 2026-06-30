// FUNC_NAME: HandleManager::isValidHandle

extern HandleManager* gHandleManager; // DAT_012234bc

struct HandleSlot {
    uint8_t unknown[0x2c]; // +0x00 to +0x2b
    uint handleID;         // +0x2c: the full handle identifier
};

bool HandleManager::isValidHandle(uint handle) {
    uint index = handle & 0xFFFF;
    if (index >= 0x200) {
        return false;
    }

    // The slots array is stored at offset 0x10 of the manager object
    HandleSlot* slot = &gHandleManager->slots[index]; // each slot is 0x30 bytes
    if (slot == nullptr) {
        return false;
    }

    if (slot->handleID == handle) {
        FUN_00414aa0(); // internal reference count or lock increment
        return true;
    }

    return false;
}