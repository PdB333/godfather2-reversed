// FUNC_NAME: PlayerController::initializePlayerData
int __thiscall PlayerController::initializePlayerData(PlayerController* this) {
    int result = 0;
    if (*(char*)((int)this + 0x1744) == '\0') {
        // Initialize 5 player slots (likely crew members or family members)
        for (int i = 0; i < 5; i++) {
            int* slotBase = (int*)((int)this + 4 + (i * 0x4a4)); // +0x488 relative offset
            *(int*)((int)slotBase + 0x488) = i; // Slot index
            FUN_005e8300(slotBase); // Initialize slot data
            FUN_005e8510();  // Some post-initialization
        }
        *(int*)((int)this + 0x173c) = 0; // Clear member count
        FUN_009c8f10(*(int*)((int)this + 0x1738)); // Release old data
        *(int*)((int)this + 0x1738) = 0; // Clear data pointer
        *(int*)((int)this + 0x1740) = 0; // Clear other member
        *(char*)((int)this + 0x1744) = 1; // Set initialized flag
        result = 1;
    }
    return result;
}