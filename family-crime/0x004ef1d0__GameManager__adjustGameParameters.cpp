//FUNC_NAME: GameManager::adjustGameParameters
void GameManager::adjustGameParameters(char applySecondSet)
{
    float fVar1;
    undefined4 uVar2;
    int in_EAX; // this pointer
    undefined4 *puVar3;
    float fVar4;
    float fVar5;

    // Check if the member variable at +0xC (likely a time or distance) is >= global threshold
    if (DAT_00e2e780 >= *(float *)(in_EAX + 0xc)) {
        if (applySecondSet != '\0') {
            // Clamp difficulty min/max and set flags for first set
            if (DAT_012058d0 < 0x16) {
                DAT_012058d0 = 0x16;
            }
            if (0x16 < DAT_00f15988) {
                DAT_00f15988 = 0x16;
            }
            _DAT_011f3a30 = 1;
            if (DAT_012058d0 < 7) {
                DAT_012058d0 = 7;
            }
            if (7 < DAT_00f15988) {
                DAT_00f15988 = 7;
            }
            _DAT_011f39f4 = 0;
            if (DAT_012058d0 < 0x19) {
                DAT_012058d0 = 0x19;
            }
            if (0x19 < DAT_00f15988) {
                DAT_00f15988 = 0x19;
            }
            _DAT_011f3a3c = 5;
            if (DAT_012058d0 < 0x18) {
                DAT_012058d0 = 0x18;
            }
            if (0x18 < DAT_00f15988) {
                DAT_00f15988 = 0x18;
            }
            _DAT_011f3a38 = 0;
            if (DAT_012058d0 < 0xf) {
                DAT_012058d0 = 0xf;
            }
            if (0xf < DAT_00f15988) {
                DAT_00f15988 = 0xf;
            }
            _DAT_011f3a14 = 0;
            if (DAT_012058d0 < 0x1b) {
                DAT_012058d0 = 0x1b;
            }
            if (0x1a < DAT_00f15988) {
                DAT_00f15988 = 0x1b;
            }
            _DAT_011f3a44 = 1;
            FUN_00417cf0(1, 2, 1); // Apply first difficulty preset
        }
        FUN_00530c90(); // Initialize subsystem A
        FUN_005311d0(); // Initialize subsystem B
        FUN_00530a60(); // Initialize subsystem C

        fVar1 = *(float *)(in_EAX + 0xc);
        fVar4 = 0.0;
        if ((0.0 < fVar1) && (fVar4 = DAT_00e2cd54, fVar1 < DAT_00e2cd54)) {
            fVar4 = fVar1;
        }
        fVar4 = fVar4 * DAT_00e2b04c;

        // Allocate and fill first structure
        puVar3 = (undefined4 *)FUN_0060cd00(5, 4, 0, 1, 0);
        uVar2 = DAT_00e2eff4;
        fVar1 = DAT_00e2b1a4;
        if (puVar3 != (undefined4 *)0x0) {
            *puVar3 = DAT_00e2eff4;
            puVar3[1] = uVar2;
            puVar3[3] = uVar2;
            puVar3[4] = uVar2;
            fVar5 = fVar4 - fVar1;
            puVar3[2] = fVar1;
            puVar3[5] = fVar5;
            puVar3[6] = fVar1;
            puVar3[7] = fVar5;
            FUN_0060cde0(); // Free or process allocation
        }

        // Allocate and fill second structure
        puVar3 = (undefined4 *)FUN_0060cd00(5, 4, 0, 1, 0);
        uVar2 = DAT_00e2eff4;
        fVar1 = DAT_00e2b1a4;
        if (puVar3 != (undefined4 *)0x0) {
            fVar4 = DAT_00e2b1a4 - fVar4;
            *puVar3 = DAT_00e2eff4;
            puVar3[1] = fVar4;
            puVar3[2] = fVar1;
            puVar3[3] = fVar4;
            puVar3[4] = uVar2;
            puVar3[5] = fVar1;
            puVar3[6] = fVar1;
            puVar3[7] = fVar1;
            FUN_0060cde0();
        }

        FUN_00612e00(); // Reset some global state

        DAT_01219950 = 0;
        DAT_01219954 = 0;
        _DAT_012199e4 = 0;
        _DAT_012199e8 = 0;

        if (applySecondSet != '\0') {
            // Clamp difficulty min/max and set flags for second set
            if (DAT_012058d0 < 0x16) {
                DAT_012058d0 = 0x16;
            }
            if (0x16 < DAT_00f15988) {
                DAT_00f15988 = 0x16;
            }
            _DAT_011f3a30 = 1;
            if (DAT_012058d0 < 7) {
                DAT_012058d0 = 7;
            }
            if (7 < DAT_00f15988) {
                DAT_00f15988 = 7;
            }
            _DAT_011f39f4 = 1;
            if (DAT_012058d0 < 0x19) {
                DAT_012058d0 = 0x19;
            }
            if (0x19 < DAT_00f15988) {
                DAT_00f15988 = 0x19;
            }
            _DAT_011f3a3c = 7;
            if (DAT_012058d0 < 0x18) {
                DAT_012058d0 = 0x18;
            }
            if (0x18 < DAT_00f15988) {
                DAT_00f15988 = 0x18;
            }
            _DAT_011f3a38 = 0;
            if (DAT_012058d0 < 0xf) {
                DAT_012058d0 = 0xf;
            }
            if (0xf < DAT_00f15988) {
                DAT_00f15988 = 0xf;
            }
            _DAT_011f3a14 = 0;
            if (DAT_012058d0 < 0x1b) {
                DAT_012058d0 = 0x1b;
            }
            if (0x1a < DAT_00f15988) {
                DAT_00f15988 = 0x1b;
            }
            _DAT_011f3a44 = 0;
            FUN_00417cf0(1, 5, 6); // Apply second difficulty preset
        }
    }
    return;
}