// FUNC_NAME: Npc::checkActionTime
// Function address: 0x00785b70
// Determines if an action can be activated based on timing constraints.
// Uses a timing table (offset 0x2C88) of structures 0x24 bytes each.
uint __thiscall Npc::checkActionTime(int this, int* pAction, int* pAnimState) {
    // pAction->actionIndex is at offset 0x04
    int actionIndex = *(int*)((char*)pAction + 4);
    
    // Pointer to timing table (array of 0x24-byte entries)
    char* pTimingTable = *(char**)(this + 0x2C88);
    
    // Round the time from the table: entry at index (actionIndex + 9)
    float timeFromTable = *(float*)(pTimingTable + (actionIndex + 9) * 0x24);
    uint roundedTime = (uint)(timeFromTable + 0.5f);  // ROUND macro equivalent
    
    // pAction->activationThreshold at offset 0x20
    uint threshold = *(uint*)((char*)pAction + 0x20);
    
    if (threshold < roundedTime) {
        // pAnimState->currentTime at offset 0x28
        uint currentTime = *(uint*)((char*)pAnimState + 0x28);
        // Global max time at offset 0x94 of timing table
        uint globalMax = *(uint*)(pTimingTable + 0x94);
        if (currentTime < globalMax) {
            // Activation allowed: return currentTime with low byte set to 1
            return (currentTime & 0xFFFFFF00) | 0x1;
        }
    }
    // Activation denied: return roundedTime with low byte cleared
    return roundedTime & 0xFFFFFF00;
}