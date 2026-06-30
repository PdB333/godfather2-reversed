// FUNC_NAME: AudioManager::activateSoundEvent
undefined4 __thiscall AudioManager::activateSoundEvent(AudioManager* this, int soundId, int* outResult) {
    int i;
    int* slotEntry;
    float tempPos[6]; // Actually used as float3 possibly but only index 0 used
    
    // Search sound slots table at offset +0x82ac (stride 0x5c, max 10 slots)
    // Slot entry: +0x00 = soundId, +0x04 = state (>=0 means active)
    i = 0;
    slotEntry = (int*)((int)this + 0x82ac);
    while ( (slotEntry[1] < 0 || (slotEntry[0] != soundId)) ) {
        i++;
        slotEntry += 0x5c / 4; // 0x5c = 92 bytes = 23 ints
        if (9 < i) {
            return 0; // Not found
        }
    }
    
    // Found slot at index i
    if (i < 0) return 0; // Should not happen
    
    // Access another array at +0x8210 (stride 0x170 = 368 bytes)
    int* soundData = (int*)((int)this + 0x8210 + i * 0x170);
    
    // Check if the referenced bank entry (at +0x81c4, stride 0x10) is valid
    int bankIndex = *(int*)((int)soundData + 0x9c); // +0x9c in soundData
    if (*(int*)((int)this + 0x81c4 + bankIndex * 0x10) == 0) {
        return 0; // Bank not loaded
    }
    
    // Get the audio engine instance
    int audioEngine = FUN_005e9d10(); // likely returns pointer to some manager
    // Get listener position? Or set 3D attributes? 
    FUN_00c9cbe0(*(undefined4*)((int)this + 0x580), *(undefined4*)(audioEngine + 0x10), 3, tempPos);
    
    // Critical section lock (global sync object)
    FUN_00ab4db0(&DAT_00e2aea0);
    
    // Read distance/volume threshold from sound data
    tempPos[0] = *(float*)((int)soundData + 0x134);
    
    if (tempPos[0] < DAT_00e2b05c) { // Global min distance?
        FUN_00ab4e70(); // unlock
        return 0;
    }
    
    // Set 3D attributes (probably position or volume)
    FUN_00c9eac0();
    FUN_00c9cd40(3, tempPos);
    FUN_00c9eae0();
    
    if (tempPos[0] <= DAT_00e2b05c) {
        *outResult = 0; // Sound distance too close?
    } else {
        *outResult = 1000; // Indicate playing?
    }
    
    FUN_00ab4e70(); // unlock
    return 1; // Success
}