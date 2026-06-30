// FUNC_NAME: EntityUpdateManager::clearDirtyFlags
// Function address: 0x0049ceb0
// Role: Clears the dirty bit (bit 1) on all elements in an update list and clears the pending update flag (bit 0) on the manager.

void __thiscall EntityUpdateManager::clearDirtyFlags(void) {
    // Check if pending update flag is set (bit 0 at offset +0xB2)
    if (this->m_pendingUpdate & 1) {
        // Get pointer to update list container at +0xA0
        UpdateList* list = this->m_updateList;
        // Number of elements stored at +0x34 relative to the container
        int count = *(int*)((char*)list + 0x34);
        // Base of element array at +0x50 relative to the container
        char* dataBase = *(char**)((char*)list + 0x50);
        char* dataEnd = dataBase + count * 0xB0; // Each element is 0xB0 bytes

        for (char* elemPtr = dataBase; elemPtr < dataEnd; elemPtr += 0xB0) {
            // Clear bit 1 (value 2) of flags at offset +8 in each element
            uint32_t* flags = (uint32_t*)(elemPtr + 8);
            *flags &= ~2; // 0xfffffffd
        }

        // Clear the pending update flag
        this->m_pendingUpdate &= ~1;
    }
}