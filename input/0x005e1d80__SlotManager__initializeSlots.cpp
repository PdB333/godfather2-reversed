// FUNC_NAME: SlotManager::initializeSlots
// Address: 0x005e1d80
// This function initializes 5 slot windows (each 0x4A4 bytes) and resets manager state.
// Returns 1 if initialization was performed, 0 if already initialized.

int SlotManager::initializeSlots() {
    int result = 0;
    // Check if already initialized (flag at +0x1744)
    if (*(char*)(this + 0x1744) == '\0') {
        // Loop over 5 slots
        for (int i = 0; i < 5; i++) {
            // Each slot begins at this+4 + i*0x4A4
            char* slotBase = reinterpret_cast<char*>(this) + 4 + i * 0x4A4;
            // Set slot's index field at offset +0x488
            *(int*)(slotBase + 0x488) = i;
            // Initialize the slot (calls FUN_005e8300)
            initSlot(slotBase); // FUN_005e8300
            // Post-initialization hook (calls FUN_005e8510)
            globalSlotPostInit(); // FUN_005e8510
        }
        // Clear selection/active index (offset +0x173C)
        *(int*)(this + 0x173C) = 0;
        // Free previous resource at +0x1738 (calls FUN_009c8F10)
        freeResource(*(void**)(this + 0x1738)); // FUN_009c8f10
        // Reset resource pointer
        *(void**)(this + 0x1738) = 0;
        // Clear another field at +0x1740
        *(int*)(this + 0x1740) = 0;
        // Mark as initialized
        *(char*)(this + 0x1744) = 1;
        result = 1;
    }
    return result;
}