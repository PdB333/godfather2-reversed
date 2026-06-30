// FUNC_NAME: MissionManager::setupMissionParameters
void __fastcall MissionManager::setupMissionParameters(int this) {
    float playerRating = *(float *)(this + 0xc);
    float threshold = DAT_00e2e780;  // global difficulty threshold?

    if (threshold < playerRating || threshold == playerRating) {
        // First configuration block - aggressive settings?
        clampDifficultyMinimum(0x16);   // DAT_012058d0 = max(0x16, g_minDifficulty)
        clampDifficultyMaximum(0x16);   // DAT_00f15988 = min(0x16, g_maxDifficulty)
        setMissionStateFlag(0, 1);      // _DAT_011f3a30 = 1
        clampDifficultyMinimum(7);
        clampDifficultyMaximum(7);
        setMissionStateFlag(1, 0);      // _DAT_011f39f4 = 0
        clampDifficultyMinimum(0x19);
        clampDifficultyMaximum(0x19);
        setMissionStateFlag(2, 5);      // _DAT_011f3a3c = 5
        clampDifficultyMinimum(0x18);
        clampDifficultyMaximum(0x18);
        setMissionStateFlag(3, 0);      // _DAT_011f3a38 = 0
        clampDifficultyMinimum(0xf);
        clampDifficultyMaximum(0xf);
        setMissionStateFlag(4, 0);      // _DAT_011f3a14 = 0
        clampDifficultyMinimum(0x1b);
        clampDifficultyMaximum(0x1b);
        setMissionStateFlag(5, (int)(in_EAX != 3)); // _DAT_011f3a44 = (in_EAX != 3)?1:0

        FUN_004ec7a0();                 // some additional init
        DAT_01219954 = DAT_012198f0;    // copy global pointers
        DAT_01219950 = DAT_012198f4;
        _DAT_01219a6c = 0;

        if (DAT_012058e8 == &DAT_01219940) {
            FUN_0060a460(DAT_012198f0); // release resource?
            FUN_0060a460(DAT_01219950);
        }

        FUN_005311d0();                 // sound? input?
        FUN_00530a60();                 // another init

        // allocate and populate a data block
        undefined4 *block = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
        if (block != 0) {
            undefined4 valA = DAT_00e2eff4;  // some constants
            undefined4 valB = DAT_00e2b1a4;
            block[0] = valA;
            block[1] = valA;
            block[2] = valB;
            block[3] = valA;
            block[4] = valB;
            block[5] = valB;
            block[6] = valA;
            block[7] = valB;
            // note: only 8 of 13 elements set? possibly rest left uninitialized
            FUN_0060cde0();             // process block?
        }

        FUN_00612e00();                 // finalize?
        DAT_01219950 = 0;
        DAT_01219954 = 0;
        _DAT_012199e4 = 0;
        _DAT_012199e8 = 0;

        // Second configuration block - defensive/reset settings?
        clampDifficultyMinimum(0x16);
        clampDifficultyMaximum(0x16);
        setMissionStateFlag(0, 1);      // _DAT_011f3a30 = 1 (same)
        clampDifficultyMinimum(7);
        clampDifficultyMaximum(7);
        setMissionStateFlag(1, 1);      // _DAT_011f39f4 = 1 (changed)
        clampDifficultyMinimum(0x19);
        clampDifficultyMaximum(0x19);
        setMissionStateFlag(2, 7);      // _DAT_011f3a3c = 7 (changed)
        clampDifficultyMinimum(0x18);
        clampDifficultyMaximum(0x18);
        setMissionStateFlag(3, 0);      // _DAT_011f3a38 = 0
        clampDifficultyMinimum(0xf);
        clampDifficultyMaximum(0xf);
        setMissionStateFlag(4, 0);      // _DAT_011f3a14 = 0
        clampDifficultyMinimum(0x1b);
        clampDifficultyMaximum(0x1b);
        setMissionStateFlag(5, 0);      // _DAT_011f3a44 = 0

        FUN_00417cf0(1, 5, 6);          // mission start? params: mode,?,?
    }
}