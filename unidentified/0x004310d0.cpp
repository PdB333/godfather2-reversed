// FUNC_004310d0: applyDisplaySettings
void applyDisplaySettings(void* param_1, void* param_2, int modeId, bool useExtraSettings)
{
    // Global state pointers (offsets from base addresses discovered via Ghidra)
    // DAT_012233b0 likely points to a display manager / mode list structure
    // +0x30: int array of 3 mode IDs (supported modes)
    // DAT_01163834 and DAT_01163650: arrays of mode-specific data
    //   DAT_01163834 stride = 0x84 (132 bytes) per entry
    //   DAT_01163650 stride = 0x210 (528 bytes) per entry

    // Enforce minimum value for resolution/refresh (e.g., width >= 0xA8 = 168)
    if (DAT_012058d4 < 0xA8) {
        DAT_012058d4 = 0xA8;
    }
    if (DAT_00f1598c > 0xA7) {   // Note: comparison reversed in original – it's if > then set to 0xA8
        DAT_00f1598c = 0xA8;
    }
    _DAT_011f3c78 = 4;   // Some configuration flag (e.g., bit depth setting)

    // Enforce another threshold (width >= 0xBE = 190)
    if (DAT_012058d4 < 0xBE) {
        DAT_012058d4 = 0xBE;
    }
    if (DAT_00f1598c > 0xBD) {
        DAT_00f1598c = 0xBE;
    }
    _DAT_011f3cd0 = 4;   // Another flag

    // Search for matching mode ID in the list of 3 supported modes
    int modeIndex = -1;
    int* modeIdArray = reinterpret_cast<int*>(DAT_012233b0 + 0x30);
    for (int i = 0; i < 3; ++i) {
        if (modeIdArray[i] == modeId) {
            modeIndex = i;
            break;
        }
    }

    int modeData1 = 0;
    void* modeData2 = nullptr;
    if (modeIndex != -1) {
        modeData1 = *(int*)(&DAT_01163834 + modeIndex * 0x84);
        modeData2 = reinterpret_cast<void*>(&DAT_01163650 + modeIndex * 0x210);
    }

    FUN_00418360(param_1, param_2, 1);
    (*(void(*)())(**(int**)PTR_DAT_0110b2dc + 0x18))();   // Call virtual function at vtable+0x18
    FUN_00419b80(modeId);
    FUN_0041a4a0(modeId, modeData1, modeData2);

    if (useExtraSettings) {
        // Apply extra display tweaks (e.g., vsync / triple buffering)
        if (DAT_012058d0 < 0x17) {
            DAT_012058d0 = 0x17;
        }
        if (DAT_00f15988 > 0x17) {
            DAT_00f15988 = 0x17;
        }
        _DAT_011f3a34 = 8;   // e.g., backbuffer count
        if (DAT_012058d0 < 0x16) {
            DAT_012058d0 = 0x16;
        }
        if (DAT_00f15988 > 0x16) {
            DAT_00f15988 = 0x16;
        }
        _DAT_011f3a30 = 3;   // e.g., present interval
    }

    FUN_00419da0(modeId, 0);

    if (useExtraSettings) {
        // Override previous extra settings (seems intentional – maybe different path)
        if (DAT_012058d0 < 0x17) {
            DAT_012058d0 = 0x17;
        }
        if (DAT_00f15988 > 0x17) {
            DAT_00f15988 = 0x17;
        }
        _DAT_011f3a34 = 4;   // Override backbuffer count
        if (DAT_012058d0 < 0x16) {
            DAT_012058d0 = 0x16;
        }
        if (DAT_00f15988 > 0x16) {
            DAT_00f15988 = 0x16;
        }
        _DAT_011f3a30 = 2;   // Override present interval
    }

    (*(void(*)())(**(int**)PTR_DAT_0110b2dc + 0x20))();   // Call virtual function at vtable+0x20
}