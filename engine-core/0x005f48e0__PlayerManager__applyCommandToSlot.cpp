// FUNC_NAME: PlayerManager::applyCommandToSlot
bool __thiscall PlayerManager::applyCommandToSlot(int thisPtr, int playerId, int command)
{
    int slotIndex;
    int dataOffset;
    int behaviorIndex;
    bool result;
    
    result = false;
    
    // Search through the slot table (10 slots, each 0x5c bytes) starting at offset +0x82ac
    // Slot structure: { int playerId; int status; ... } 
    slotIndex = 0;
    int* slotEntry = (int*)(thisPtr + 0x82ac);
    while ((slotEntry[1] < 0 || slotEntry[0] != playerId)) {
        slotIndex++;
        slotEntry += 0x5c / sizeof(int); // 0x5c bytes -> 23 ints (0x17)
        if (slotIndex > 9) {
            return false;
        }
    }
    
    if (slotIndex < 0) {
        return false;
    }
    
    // Access the per-slot data structure at +0x8210 with stride 0x170
    int slotDataBase = thisPtr + 0x8210 + slotIndex * 0x170;
    
    // Grab a mutex
    FUN_00ab4db0(&DAT_00e2aea0);  // Lock (likely a global mutex)
    
    // Offset 0x9c in slot data: an index into an array of behaviors (stride 0x10) at +0x81c4
    int behaviorIdx = *(int*)(slotDataBase + 0x9c);
    dataOffset = behaviorIdx * 0x10;
    int* behaviorPtr = (int*)(thisPtr + 0x81c4 + dataOffset);
    int behaviorData = *behaviorPtr;
    
    if (behaviorData != 0) {
        // Check if a cooldown timer (float at +0x134) has elapsed and system is ready
        if ((*(float*)(slotDataBase + 0x134) >= DAT_00e2b05c) && (FUN_005e9d10() != 0)) {
            // Store the command at +0x94 in slot data
            *(int*)(slotDataBase + 0x94) = command;
            
            // Play audio/sound effects for this command
            FUN_00c9eac0();          // Prepare audio context
            FUN_00ca4e90(0, command); // Play sound associated with command
            FUN_00c9eae0();          // Finalize audio
            
            result = true;
        }
        
        // Notify the behavior system with behavior pointer and some related data
        // Reads from another field in the behavior array at +0x81c0 (previous entry)
        int notifyParam = *(int*)(thisPtr + 0x81c0 + dataOffset);
        FUN_005ebfa0(thisPtr, notifyParam, behaviorData);
    }
    
    FUN_00ab4e70(); // Unlock mutex
    return result;
}