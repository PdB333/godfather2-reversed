// FUNC_NAME: DisplaySettings::applySettings
// Address: 0x00431f50
// Role: Applies display/graphics settings (resolution, gamma, scissor rects) for current game mode

void DisplaySettings::applySettings() {
    // +0x39f8: current game mode (1=menu frontend, 3= maybe loading? else in-game)
    if (*(int*)(this + 0x39f8) == 1) {
        // Transition to full-screen menu mode
        *(int*)(this + 0x108c) = 2;   // +0x108c: mode state (1=windowed,2=fullscreen)
        *(int*)(this + 0x1090) = 1;   // +0x1090: related state (maybe buffering mode)
        
        int fsOffset = *(int*)(**(int**)(__readfsdword(0x2c) + 0x34)); // thread-local storage
        *(int*)(this + 0x1098) = (&DAT_00f15a4c)[fsOffset == 0]; // +0x1098: something pointer
        // DAT_00f15a4c indexed by fsOffset (maybe window handle or rendering device)
        (&DAT_00f15a4c)[fsOffset == 0] = 0;
        
        int iVar6;
        if (fsOffset != 0) {
            iVar6 = DAT_012068e8;
        } else {
            iVar6 = DAT_01206880;
        }
        // Rebuild a pointer table (likely for rendering callbacks)
        **(int**)(iVar6 + 0x14) = &PTR_LAB_01127524;
        *(int*)(iVar6 + 0x14) = *(int*)(iVar6 + 0x14) + 4;
        **(int**)(iVar6 + 0x14) = 0;
        *(int*)(iVar6 + 0x14) = *(int*)(iVar6 + 0x14) + 4;
    } else {
        // In-game mode: set windowed
        *(int*)(this + 0x108c) = 1;
        *(int*)(this + 0x1090) = 2;
    }
    
    // Clamp global gamma/brightness values (DAT_012058d0 and DAT_00f15988 represent current gamma)
    if (DAT_012058d0 < 14) DAT_012058d0 = 14;
    if (DAT_00f15988 > 14) DAT_00f15988 = 14;
    
    _DAT_011f3a10 = 0; // Some flag (maybe vsync)
    if (DAT_012058d0 < 7) DAT_012058d0 = 7;
    if (DAT_00f15988 > 7) DAT_00f15988 = 7;
    
    _DAT_011f39f4 = 1; // Another flag
    
    setGamma(*(int*)(this + 0x108c)); // Uses the mode state
    
    *(unsigned int*)(this + 0x80) = DAT_011f38f0; // +0x80: current display mode index
    
    unsigned int modeIdx = DAT_01205434; // default mode index
    if ((*(int*)(this + 0x39f8) != 0) && (*(int*)(this + 0x39f8) != 3)) {
        modeIdx = DAT_01205438; // alternate mode for in-game
    }
    
    char* modeEntry;
    if (modeIdx < 0x1000) {
        modeEntry = &DAT_011a0f28 + modeIdx * 0x38; // mode entry array (0x38 bytes each)
    } else {
        modeEntry = nullptr;
    }
    
    if (modeEntry) {
        *(unsigned short*)(this + 0x1220) = *(unsigned short*)(modeEntry + 2); // +0x1220: width
        *(unsigned short*)(this + 0x1222) = *(unsigned short*)(modeEntry + 4); // +0x1222: height
    }
    
    copyMatrix(this + 0x10e0, this + 0x1120); // copy transformation matrices
    setClearColor(0, 1.0f); // clear color
    
    // Set flag at +0x1094 based on game mode (true if menu/loading)
    char isMenuMode = (*(int*)(this + 0x39f8) == 1 || *(int*)(this + 0x39f8) == 3);
    *(char*)(this + 0x1094) = isMenuMode;
    
    if (!isMenuMode && DAT_0120535b != 0) {
        // In-game with some specific flag: adjust rendering state
        unsigned int savedWidth = DAT_011f38f0;
        unsigned int savedHeight = DAT_011f38f4;
        
        if (*(int*)(*(int*)(DAT_012233a8 + 4) + 0x39f8) != 0) {
            DAT_011f38f0 = DAT_0120536c; // special width
        } else {
            DAT_011f38f0 = DAT_012118c0; // default width
        }
        DAT_011f38f4 = 0;
        
        setRenderTarget(0, savedWidth, savedHeight);
        setViewport(0, 0, 0, 1.0f, 1.0f);
        clearScreen(0, 0, 0, 0, 1.0f, 0);
        
        if (DAT_012058d4 < 168) DAT_012058d4 = 168;
        if (DAT_00f1598c > 167) DAT_00f1598c = 168;
        _DAT_011f3c78 = 2;
        if (DAT_012058d4 < 190) DAT_012058d4 = 190;
        if (DAT_00f1598c > 189) DAT_00f1598c = 190;
        _DAT_011f3cd0 = 2;
        
        setScissorRect(1);
        if (DAT_012058d4 < 168) DAT_012058d4 = 168;
        if (DAT_00f1598c > 167) DAT_00f1598c = 168;
        _DAT_011f3c78 = 15;
        if (DAT_012058d4 < 190) DAT_012058d4 = 190;
        if (DAT_00f1598c > 189) DAT_00f1598c = 190;
        _DAT_011f3cd0 = 15;
        setScissorEnable(1);
        
        unsigned int temp1 = DAT_011f38f4;
        unsigned int temp2 = DAT_011f38f0;
        DAT_011f38f4 = 0;
        DAT_011f38f0 = savedWidth;
        setRenderTarget(0, temp2, temp1);
        setViewport(0, 0, 0, 1.0f, 1.0f);
        
        *(char*)(this + 0x1094) = 1; // override to menu mode?
    }
    
    // Determine another flag at +0x1095 (maybe for cutscene or widescreen)
    if (DAT_01205359 == 0 || *(char*)(this + 0x1094) != 0) {
        *(char*)(this + 0x1095) = 0;
    } else {
        *(char*)(this + 0x1095) = 1;
    }
    
    if (*(char*)(this + 0x1095) != 0) {
        // Setup additional UI transformation matrices
        setupUITransforms(this, this + 0x1160, this + 0x10d0, this + 0x1120, this + 0x10e0);
    }
    
    // Set final display mode
    unsigned int finalMode = modeIdx;
    unsigned int prevWidth = DAT_011f38f0;
    unsigned int prevHeight = DAT_011f38f4;
    DAT_011f38f4 = 0;
    DAT_011f38f0 = finalMode;
    setRenderTarget(0, prevWidth, prevHeight);
    setScissorRect(15);
    DAT_012058f4 = finalMode; // current mode index
    
    if (DAT_012058e8 != 0 && *(int*)(DAT_012058e8 + 0xa0) != 0) {
        resetAccumulation(); // clears accumulation buffer
    }
    
    // Final gamma clamps and flags
    if (DAT_012058d0 < 23) DAT_012058d0 = 23;
    if (DAT_00f15988 > 23) DAT_00f15988 = 23;
    _DAT_011f3a34 = 4; // gamma curve?
    
    if (DAT_012058d0 < 14) DAT_012058d0 = 14;
    if (DAT_00f15988 > 14) DAT_00f15988 = 14;
    _DAT_011f3a10 = 0;
    
    setGamma(*(int*)(this + 0x108c));
    setDithering(1, 2, 2); // dithering parameters
    
    if (DAT_012058d0 < 27) DAT_012058d0 = 27;
    if (DAT_00f15988 > 26) DAT_00f15988 = 27;
    _DAT_011f3a44 = 1;
    
    if (DAT_012058d0 < 25) DAT_012058d0 = 25;
    if (DAT_00f15988 > 25) DAT_00f15988 = 25;
    _DAT_011f3a3c = 7;
    
    if (DAT_012058d0 < 24) DAT_012058d0 = 24;
    if (DAT_00f15988 > 24) DAT_00f15988 = 24;
    _DAT_011f3a38 = 0;
    
    if (DAT_012058d0 < 15) DAT_012058d0 = 15;
    _DAT_011f3a14 = 0;
    if (DAT_00f15988 > 15) DAT_00f15988 = 15;
}