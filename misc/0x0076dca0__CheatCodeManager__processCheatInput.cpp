// FUNC_NAME: CheatCodeManager::processCheatInput
undefined4 * __thiscall CheatCodeManager::processCheatInput(CheatCodeManager *this, uint cheatId, void *pManager) {
    int *gameData;
    int codeCheckResult;
    byte cheatEnabled;
    int *pData;
    int baseOffset;
    uint soundId;
    uint somethingFlag;
    uint result;

    // Call base class constructor
    baseConstructor(cheatId, pManager);
    
    // Set vtable pointer and initialize fields
    this->vtable = &CheatCodeManager_VTable;
    this->field_0x70 = 0;           // +0x1c * 4 = 0x70? Actually param_1[0x1c] is offset 0x70
    *(byte *)&this->field_0x74 = 0; // +0x1d * 4 = 0x74
    this->field_0x78 = 0;           // +0x1e * 4 = 0x78

    // Get game data pointer from this+0x5C (param_1[0x17])
    gameData = (int *)this->gameDataPtr; // +0x5C
    
    if (gameData != NULL) {
        pManager = (void *)FUN_0043b870(DAT_01131040); // Allocate something
    } else {
        pManager = NULL;
    }

    // Static initialization call
    FUN_0076dc20();

    // Check if cheats are enabled globally
    cheatEnabled = FUN_007f8f10();
    if (cheatEnabled == 0) {
        // Access large offsets in gameData structure
        codeCheckResult = gameData[0x7b5]; // Offset 0x1ED4? (0x7b5*4)
        if (gameData[0x7b6] != 0) {
            baseOffset = gameData[0x7b6] - 0x48; // Adjust pointer
        } else {
            baseOffset = 0;
        }
        
        // Get a value from offset +0x88 within that structure
        uint *pCodeEntry = (uint *)(baseOffset + 0x88);
        uint storedCode = *pCodeEntry;
        
        // Compare cheat ID with stored code (masked/flags)
        result = FUN_009b1a60(&storedCode, 0x10000, 0x40, 1);
        
        if ((result != 0) || (codeCheckResult == 0x637b907)) {
            // Check a global setting
            int settings = FUN_0043b870(DAT_01130950);
            if ((settings == 0) || ((*(uint *)(settings + 0x4c) >> 1 & 1) == 0)) {
                // Debug output event 0x17 (23)
                FUN_007f63e0(0x17);
                
                // Set a timer or value
                this->field_0x70 = gameData[0x764] + DAT_01205224;
                
                if (codeCheckResult == 0x637b907) {
                    // Unlock credits or special feature
                    FUN_0093cc60(this->gameDataPtr);
                    *(byte *)&this->field_0x74 |= 2;
                    
                    somethingFlag = 0;
                    // Start sound context
                    FUN_006fbc40(0, 0);
                    
                    if (result == 0) {
                        soundId = 0xab4408; // Failure sound (maybe)
                    } else {
                        soundId = 0x2135b26; // Success sound
                    }
                    
                    // Play sound
                    FUN_007f96a0(soundId, 0, someSoundContext, somethingFlag);
                    // End sound context
                    FUN_006fbc70();
                }
                
                if (pManager != NULL) {
                    // Check permission via pManager's vtable
                    if ((*(code **)(*(int *)pManager + 0x1c))(0x100) != 0) {
                        FUN_007fff40(&DAT_0112ae00);
                    }
                }
            }
        }
    }

    // Second permission check perhaps for different overlay
    if (pManager != NULL) {
        if ((*(code **)(*(int *)pManager + 0x1c))(0x100) != 0) {
            FUN_0081f300();
        }
    }

    // Notify gameData object with event (3,1)
    (*(code **)(*(int *)gameData + 0x234))(3, 1);

    return this;
}