// FUNC_NAME: TeamScenario::Constructor
void __thiscall TeamScenario::Constructor(void* thisPtr, int playerSlot, int teamId) {
    // Global singleton pointer (likely MultiplayerManager or GameManager)
    void* g_pManager = *(void**)0x00e2b1a4;
    
    // Base vtable (likely some base class)
    *(void**)thisPtr = (void*)0x00e32a8c;
    
    // Initialize fields
    *(int*)((char*)thisPtr + 0x60) = 0;   // +0x60: some pointer or flag
    *(int*)((char*)thisPtr + 0x50) = 0;   // +0x50: some pointer or flag
    *(void**)((char*)thisPtr + 0x20) = g_pManager;  // +0x20: store global manager
    *(int*)((char*)thisPtr + 0x24) = -1;  // +0x24: -1 sentinel
    *(int*)((char*)thisPtr + 0x30) = -1;  // +0x30: -1 sentinel
    *(void**)((char*)thisPtr + 0x04) = g_pManager;  // +0x04: duplicate manager pointer
    
    // Slot count and ID
    int* slotCount = (int*)((char*)thisPtr + 0x88); // +0x88: number of stored slots
    *slotCount = 0;
    *(int*)((char*)thisPtr + 0x8C) = teamId;        // +0x8C: team/type identifier
    
    // Add initial player slot (max 4 slots)
    if (*slotCount < 4) {
        int* slotArray = (int*)((char*)thisPtr + 0x78); // +0x78: array of 4 ints (slots)
        slotArray[*slotCount] = playerSlot;              // Store player slot index
        (*slotCount)++;
    }
    
    // Get value from another global structure
    void* globalStruct = *(void**)0x01223480;
    *(int*)((char*)thisPtr + 0x70) = *(int*)((char*)globalStruct + 0x24); // +0x70: some game state
    
    // Switch to derived vtable
    *(void**)thisPtr = (void*)0x00e39c58;
    
    // Store self-pointer for internal use
    *(void**)((char*)thisPtr + 0x74) = thisPtr; // +0x74: back pointer
}