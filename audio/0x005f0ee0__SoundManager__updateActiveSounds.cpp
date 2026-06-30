// FUNC_NAME: SoundManager::updateActiveSounds
void SoundManager::updateActiveSounds(int param_1, SoundList* soundList)
{
    int currentSound;
    int nextSound;
    char globalFlag;
    char isPlaying;
    int* someGlobalPtr;
    
    globalFlag = DAT_0120569e;
    someGlobalPtr = DAT_01223510;
    
    // Process sounds in the pending list (index 3)
    for (currentSound = soundList[3]; currentSound != 0; currentSound = *(int*)(currentSound + 4)) {
        if (someGlobalPtr != (int*)0x0) {
            FUN_005ebbe0(someGlobalPtr); // Likely some update/check function
            someGlobalPtr = DAT_01223510;
        }
    }
    
    // Process sounds in the main list (index 0)
    currentSound = *soundList;
    while (nextSound = currentSound, nextSound != 0) {
        if (someGlobalPtr != (int*)0x0) {
            FUN_005ebbe0(someGlobalPtr);
            someGlobalPtr = DAT_01223510;
        }
        currentSound = *(int*)(nextSound + 4); // Next sound in linked list
        
        // Call function with sound parameters: soundId (+0x8), volume (+0x18), 
        // loop flag (+0x10 bit 5), fadeTime (+0x1d), someFlag (+0x24)
        FUN_005dbc10(*(undefined2*)(nextSound + 8), 
                     *(undefined4*)(nextSound + 0x18),
                     (*(byte*)(nextSound + 0x10) >> 5) & 1,
                     (int)*(char*)(nextSound + 0x1d),
                     *(undefined4*)(nextSound + 0x24));
        
        if ((*(byte*)(nextSound + 0x10) & 0x20) == 0) { // Check if not looping
            if (*(char*)(nextSound + 0x1d) < 1) { // fadeTime <= 0
                isPlaying = (**(code**)(*someGlobalPtr + 0x3c))(*(undefined2*)(nextSound + 8)); // Check if sound is playing
                someGlobalPtr = DAT_01223510;
                if (isPlaying != '\0') {
                    FUN_005dbc10(*(undefined2*)(nextSound + 8)); // Stop sound
                    FUN_005f12a0(); // Cleanup/remove from list
                    someGlobalPtr = DAT_01223510;
                }
            } else {
                *(char*)(nextSound + 0x1d) = *(char*)(nextSound + 0x1d) - 1; // Decrement fade timer
            }
        }
    }
    
    // Second pass if globalFlag is set
    if (globalFlag != '\0') {
        currentSound = *soundList;
        while (nextSound = currentSound, nextSound != 0) {
            currentSound = *(int*)(nextSound + 4);
            
            FUN_005dbc10(*(undefined2*)(nextSound + 8), 
                         *(undefined4*)(nextSound + 0x18),
                         (*(byte*)(nextSound + 0x10) >> 5) & 1,
                         (int)*(char*)(nextSound + 0x1d),
                         *(undefined4*)(nextSound + 0x24));
            
            if ((*(int*)(nextSound + 0x24) == 0) && // Check someFlag
                (isPlaying = (**(code**)(*someGlobalPtr + 0x3c))(*(undefined2*)(nextSound + 8)), 
                 someGlobalPtr = DAT_01223510,
                 isPlaying == '\0')) { // Sound is not playing
                *(ushort*)(nextSound + 0x10) = *(ushort*)(nextSound + 0x10) & 0xffbf; // Clear bit 6
                (**(code**)(*someGlobalPtr + 0x20))(*(undefined2*)(nextSound + 8)); // Release sound
                FUN_005dbc10(*(undefined2*)(nextSound + 8), *(undefined4*)(nextSound + 0x18)); // Update volume
                someGlobalPtr = DAT_01223510;
                if ((*(byte*)(nextSound + 0x10) & 0x40) == 0) { // Check bit 6
                    FUN_005f1660(); // Remove sound from active list
                    someGlobalPtr = DAT_01223510;
                }
            }
        }
    }
    return;
}