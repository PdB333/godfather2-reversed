// FUNC_NAME: TargetingManager::updateSnapState
void __fastcall TargetingManager::updateSnapState(TargetingManager* this) {
    uint32 savedState = *(uint32*)((uint8*)this + 0x118);
    
    // Get current world position (target/camera/player)
    void* posSource = FUN_00471610();  // Returns a pointer to position data
    double packedXY = *(double*)((uint8*)posSource + 0x30);  // XY packed as double
    float posZ = *(float*)((uint8*)posSource + 0x38);
    
    float posX = (float)packedXY;
    float posY = (float)((unsigned long long)packedXY >> 32);
    
    float deltaX, deltaY, deltaZ;
    uint32 savedZ_B4;  // Actually a float stored at +0xB4
    uint64 savedPos_AC;  // Two floats packed at +0xAC
    float sqDistNew = 0.0f;
    uint64 oldPos = 0;
    
    FUN_007c83a0();  // Possibly updateTimers or deltaTime update
    
    bool wasSnapped = (*(uint8*)((uint8*)this + 0x128) & 1) != 0;
    if (!wasSnapped) {
        savedZ_B4 = 0;
    } else {
        deltaX = posX - *(float*)((uint8*)this + 0xAC);
        savedZ_B4 = *(uint32*)((uint8*)this + 0xB4);
        deltaY = posY - *(float*)((uint8*)this + 0xB0);
        deltaZ = posZ - *(float*)((uint8*)this + 0xB4);
        sqDistNew = deltaZ*deltaZ + deltaY*deltaY + deltaX*deltaX;
        oldPos = *(uint64*)((uint8*)this + 0xAC);
    }
    
    // Toggle between state 1 and 2
    *(uint32*)((uint8*)this + 0x118) = 2 - (uint32)(*(int32*)((uint8*)this + 0x118) != 1);
    
    FUN_007c83a0();  // Another timer update
    
    // Conditional snap refresh
    bool bit0 = (*(uint8*)((uint8*)this + 0x128) & 1) != 0;
    if ((!bit0 || (!wasSnapped && sqDistNew <= sqDistNew)) && 
        (*(uint32*)((uint8*)this + 0x118) = savedState, !wasSnapped)) {
        // This condition runs only when wasSnapped is false (i.e., not snapped)
        // and either bit0 is clear OR (wasSnapped false and distance condition)
        // Actually: if wasSnapped is false, the condition can proceed.
        // Then it sets the snapped flag and stores current position.
        *(uint32*)((uint8*)this + 0x128) |= 1;
        *(uint64*)((uint8*)this + 0xAC) = oldPos;
        *(uint32*)((uint8*)this + 0xB4) = savedZ_B4;
    }
    
    // Play sound effects based on new state
    if (*(int32*)((uint8*)this + 0x118) == 1) {
        // State 1: play snap sound, stop unsnap sound
        FUN_007f63e0(0x1D);  // Start sound 0x1D
        FUN_007f6420(0x1E);  // Stop sound 0x1E
    } else {
        // State 2: play unsnap sound, stop snap sound
        FUN_007f63e0(0x1E);  // Start sound 0x1E
        FUN_007f6420(0x1D);  // Stop sound 0x1D
    }
}