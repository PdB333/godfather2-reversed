// FUNC_NAME: GodfatherGameManager::processGlobalState
void GodfatherGameManager::processGlobalState(void)
{
    int state; // unaff_EDI - presumably 'this' or state ID stored in EDI
    
    if (state == 0) {
        // State 0: Enter initial state
        if (DAT_012058d0 < 0x3b) {      // +0x00: global min FPS cap, clamp to 59
            DAT_012058d0 = 0x3b;
        }
        if (0x3b < DAT_00f15988) {      // +0x00: global max FPS cap, clamp to 59
            DAT_00f15988 = 0x3b;
        }
        _DAT_011f3ac4 = 0xffffffff;     // +0x00: state duration timer
        FUN_0041e4d0(1,1,1);            // setGraphicsDetail(High, High, High)
        if (DAT_012058d0 < 0x38) {      // clamp FPS min to 56
            DAT_012058d0 = 0x38;
        }
        if (0x38 < DAT_00f15988) {      // clamp FPS max to 56
            DAT_00f15988 = 0x38;
        }
        _DAT_011f3ab8 = 8;              // +0x00: some state transition timer
        if (DAT_012058d0 < 0x39) {      // clamp FPS min to 57
            DAT_012058d0 = 0x39;
        }
        if (0x39 < DAT_00f15988) {      // clamp FPS max to 57
            DAT_00f15988 = 0x39;
        }
        _DAT_011f3abc = 0;              // +0x00: some flag
        if (DAT_012058d0 < 0x3a) {      // clamp FPS min to 58
            DAT_012058d0 = 0x3a;
        }
        if (0x3a < DAT_00f15988) {      // clamp FPS max to 58
            DAT_00f15988 = 0x3a;
        }
        _DAT_011f3ac0 = 0xffffffff;     // +0x00: state duration timer
        if (DAT_012058d0 < 0x34) {      // clamp FPS min to 52
            DAT_012058d0 = 0x34;
        }
        if (0x34 < DAT_00f15988) {      // clamp FPS max to 52
            DAT_00f15988 = 0x34;
        }
        _DAT_011f3aa8 = 0;              // +0x00: current global state
        DAT_011f41d8 = state;           // +0x00: store state ID
        return;
    }
    if (state == 1) {
        // State 1: Active gameplay state
        FUN_0042a720(DAT_011f41f4);     // applyGlobalRenderSettings(videoFlags)
        FUN_0041e4d0(DAT_011f41dc, DAT_011f41e0, DAT_011f41e4); // setGraphicsDetail from saved settings
        FUN_0041e560(DAT_011f41e8, DAT_011f41ec, DAT_011f41f0); // setAudioSettings(...)
        if (DAT_012058d0 < 0x34) {      // clamp FPS min to 52
            DAT_012058d0 = 0x34;
        }
        if (0x34 < DAT_00f15988) {      // clamp FPS max to 52
            DAT_00f15988 = 0x34;
        }
        DAT_011f41f8 = 0;               // +0x00: some flag
        _DAT_011f3aa8 = 1;              // +0x00: set current global state to 1
        DAT_011f41d8 = state;           // +0x00: store state ID
        return;
    }
    // Default/other states: clamp FPS to 59, set state timer to 0, apply graphics and audio settings
    if (DAT_012058d0 < 0x3b) {
        DAT_012058d0 = 0x3b;
    }
    if (0x3b < DAT_00f15988) {
        DAT_00f15988 = 0x3b;
    }
    _DAT_011f3ac4 = 0;                  // +0x00: clear state timer
    FUN_0041e4d0(1,1,1);                // setGraphicsDetail(High, High, High)
    FUN_0041e560(DAT_011f41e8, DAT_011f41ec, DAT_011f41f0); // apply audio settings
    if (DAT_012058d0 < 0x34) {
        DAT_012058d0 = 0x34;
    }
    if (0x34 < DAT_00f15988) {
        DAT_00f15988 = 0x34;
    }
    _DAT_011f3aa8 = 1;                  // +0x00: set current global state to 1
    DAT_011f41d8 = state;               // +0x00: store state ID
    return;
}