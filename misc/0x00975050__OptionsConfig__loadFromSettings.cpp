// FUNC_NAME: OptionsConfig::loadFromSettings
void __fastcall OptionsConfig::loadFromSettings(int thisPtr)
{
    // Global pointer to settings data (likely a singleton)
    int* settingsBase = DAT_01129938;
    
    // Get a boolean from some function (maybe "isInitialized" or "isReady")
    bool flag = FUN_0090cbe0();
    *(bool*)(thisPtr + 0x68) = flag;
    
    // Save original state to restore later
    int originalState = *(int*)(thisPtr + 0x5c);
    
    // Set initial state to 2 (first phase)
    *(int*)(thisPtr + 0x5c) = 2;
    *(int*)(thisPtr + 0x60) = 0; // sub-state counter
    
    // Phase 1: process cases 0-6
    while (true) {
        switch (*(int*)(thisPtr + 0x60)) {
            case 0:
                // Bit 1 (0x02) of settings field at +0x14
                *(uint32_t*)(thisPtr + 0x64) = (*(uint32_t*)(settingsBase + 0x14) >> 1) & 1;
                break;
            case 1:
                // Bit 2 (0x04)
                *(uint32_t*)(thisPtr + 0x64) = (*(uint32_t*)(settingsBase + 0x14) >> 2) & 1;
                break;
            case 2:
            {
                // Bit 3 (0x08) but with complicated calculation? Actually goes to LAB_009751c4 (direct assignment)
                uint32_t bitVal = (*(uint32_t*)(settingsBase + 0x14) >> 3) & 1;
                // Jump to final assignment at LAB_009751c4
                *(uint32_t*)(thisPtr + 0x64) = bitVal;
                break;
            }
            case 3:
                // Bit 4 (0x10)
                *(uint32_t*)(thisPtr + 0x64) = (*(uint32_t*)(settingsBase + 0x14) >> 4) & 1;
                break;
            case 4:
                // Bit 5 (0x20)
                *(uint32_t*)(thisPtr + 0x64) = (*(uint32_t*)(settingsBase + 0x14) >> 5) & 1;
                break;
            case 5:
            {
                // Float scaling from settings +0x20
                float fVal = (*(float*)(settingsBase + 0x20) - DAT_00d8f7e8) / DAT_00e57588;
                float clamped;
                if (fVal > 0.0f) {
                    clamped = (fVal > _DAT_00d5780c) ? _DAT_00d5780c : fVal;
                } else {
                    clamped = 0.0f;
                }
                float scaled = clamped * DAT_00d5d7b8;
                float result;
                if (scaled <= 0.0f) {
                    // Branch: recompute raw clamp and subtract constant
                    if (fVal > 0.0f) {
                        fVal = (fVal > _DAT_00d5780c) ? _DAT_00d5780c : fVal;
                    } else {
                        fVal = 0.0f;
                    }
                    result = fVal * DAT_00d5d7b8 - _DAT_00d5c458;
                } else {
                    if (fVal > 0.0f) {
                        fVal = (fVal > _DAT_00d5780c) ? _DAT_00d5780c : fVal;
                        result = fVal * DAT_00d5d7b8 + _DAT_00d5c458;
                    } else {
                        result = DAT_00d5d7b8 * 0.0f + _DAT_00d5c458;
                    }
                }
                *(uint32_t*)(thisPtr + 0x64) = (uint32_t)result;
                break;
            }
            case 6:
            {
                // Similar but using settings +0x24 and different divisor
                float fVal = (*(float*)(settingsBase + 0x24) - DAT_00d8f7e8) / DAT_00e5758c;
                float clamped;
                if (fVal > 0.0f) {
                    clamped = (fVal > _DAT_00d5780c) ? _DAT_00d5780c : fVal;
                } else {
                    clamped = 0.0f;
                }
                float scaled = clamped * DAT_00d5d7b8;
                float result;
                if (scaled <= 0.0f) {
                    // Jump to LAB_009751a6 logic
                    if (fVal > 0.0f) {
                        fVal = (fVal > _DAT_00d5780c) ? _DAT_00d5780c : fVal;
                    } else {
                        fVal = 0.0f;
                    }
                    result = fVal * DAT_00d5d7b8 - _DAT_00d5c458;
                } else {
                    if (fVal > 0.0f) {
                        fVal = (fVal > _DAT_00d5780c) ? _DAT_00d5780c : fVal;
                        result = fVal * DAT_00d5d7b8 + _DAT_00d5c458;
                    } else {
                        result = DAT_00d5d7b8 * 0.0f + _DAT_00d5c458;
                    }
                }
                *(uint32_t*)(thisPtr + 0x64) = (uint32_t)result;
                break;
            }
        }
        
        // Call "InitOptionValue" with pointer to some string constant
        FUN_005a04a0("InitOptionValue", 0, &DAT_00d8f7f8, 0);
        
        // Increment sub-state
        *(int*)(thisPtr + 0x60) = *(int*)(thisPtr + 0x60) + 1;
        
        // If sub-state > 6, move to phase 2
        if (*(uint32_t*)(thisPtr + 0x60) > 6) {
            *(int*)(thisPtr + 0x5c) = 3;
            *(int*)(thisPtr + 0x60) = 0;
            
            // Phase 2: process indices 0-2
            do {
                int idx = *(int*)(thisPtr + 0x60);
                if (idx == 0) {
                    // Bit 0 of settings +0x14
                    *(uint32_t*)(thisPtr + 0x64) = *(uint8_t*)(settingsBase + 0x14) & 1;
                } else if (idx == 1) {
                    // Float at settings +0x18, scaled
                    *(int*)(thisPtr + 0x64) = (int)(*(float*)(settingsBase + 0x18) * DAT_00d5d7b8);
                } else if (idx == 2) {
                    // Float at settings +0x1c, scaled
                    *(int*)(thisPtr + 0x64) = (int)(*(float*)(settingsBase + 0x1c) * DAT_00d5d7b8);
                }
                FUN_005a04a0("InitOptionValue", 0, &DAT_00d8f7f8, 0);
                *(int*)(thisPtr + 0x60) = *(int*)(thisPtr + 0x60) + 1;
            } while (*(uint32_t*)(thisPtr + 0x60) < 3);
            
            // Restore original state and return
            *(int*)(thisPtr + 0x5c) = originalState;
            return;
        }
    }
}