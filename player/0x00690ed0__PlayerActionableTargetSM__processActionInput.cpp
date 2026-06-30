// FUNC_NAME: PlayerActionableTargetSM::processActionInput

void __thiscall PlayerActionableTargetSM::processActionInput(int thisPtr, int inputEntityId, undefined4 actionHash, float *analogInput)
{
    uint flag;
    undefined4 uVar2;
    int gameMode;
    byte bVar4;
    char cVar5;
    int iVar6;
    int iVar10;
    undefined4 *actionConfig;
    undefined4 uVar8;
    undefined4 uVar9;
    int toggleFlag;

    iVar6 = DAT_01223464;
    if (DAT_012233a0 == 0) {
        return;
    }
    iVar10 = **(int **)(DAT_012233a0 + 4);  // Dereference global pointer chain to get some ID
    if (iVar10 == 0) {
        return;
    }
    if (iVar10 == 0x1f30) {  // Specific invalid/cancelled state
        return;
    }
    gameMode = FUN_007a5f40();  // Get current game mode (0=menu, 1=gameplay, etc.)
    flag = *(uint *)(iVar10 + -0x1650);  // Read flag from some global data (offset negative? likely a hash or state index)
    bVar4 = FUN_00690e60(0x17a26743, inputEntityId, actionHash);  // Check first action trigger
    bVar4 = (byte)(flag >> 1) & 1 | bVar4;  // Combine with global flag bit

    actionConfig = (undefined4 *)FUN_004973e0(0x776def75);  // Lookup action configuration by hash
    if (actionConfig != (undefined4 *)0x0) {
        if (*(char *)(inputEntityId + 0x1bb) != '\0') {  // Check some entity flag (e.g., isAlive?)
            *(undefined1 *)(thisPtr + 0x10) = 1;   // Set state flags: active
            *(undefined1 *)(thisPtr + 0x11) = 0;   // movement flag
            *(undefined1 *)(thisPtr + 0x12) = 0;   // other flag
            *(undefined1 *)(thisPtr + 0x13) = 0;   // toggle flag
        }
        uVar9 = *actionConfig;          // Some action config data
        uVar2 = actionConfig[1];
        if (*(char *)(thisPtr + 0x10) == '\0') {  // If not already active
            iVar10 = thisPtr + 0x11;
            uVar8 = FUN_0049a890(uVar9, uVar2, iVar10);  // Evaluate condition based on config and state
            cVar5 = FUN_006904e0(actionHash, uVar8, iVar10);  // Check if condition matches
            if (cVar5 == '\0') {
                iVar10 = thisPtr + 0x12;
                uVar9 = FUN_0049a8b0(uVar9, uVar2, iVar10);  // Another condition evaluation
                cVar5 = FUN_006904e0(actionHash, uVar9, iVar10);
                if (cVar5 == '\0') goto LAB_00691063;  // No condition triggered, skip
            }
            if (bVar4 == 0) {  // No combined flag
                if (gameMode != 2) {  // Not in a specific mode (e.g., not in cutscene/replay)
                    *(uint *)(thisPtr + 0xc) = (uint)(*(int *)(thisPtr + 0xc) == 0);  // Toggle state
                }
            }
            else {
                bVar4 = 0;
                *(undefined4 *)(thisPtr + 0xc) = 1;  // Set state to 1
                if (iVar6 != 0) {  // If some global flag is set (e.g., audio enabled)
                    uVar9 = FUN_00798f50(1);  // Load sound ID for action start
                    FUN_00466880(uVar9);  // Play sound
                }
            }
        }
        else {  // Already active
            cVar5 = FUN_0049a890(uVar9, uVar2);  // Check condition without state offset
            if ((((cVar5 == '\0') || (cVar5 == -1)) || (cVar5 = FUN_00b930b0(cVar5), cVar5 == '\0')) &&
               (((cVar5 = FUN_0049a8b0(uVar9, uVar2), cVar5 == '\0' || (cVar5 == -1)) ||
                (cVar5 = FUN_00b930b0(cVar5), cVar5 == '\0')))) {
                *(undefined1 *)(thisPtr + 0x10) = 0;  // Deactivate on missing conditions
            }
        }
    }

LAB_00691063:
    iVar10 = *(int *)(thisPtr + 0xc);  // Current toggle state
    if (bVar4 != 0) {   // If combined flag overrides
        iVar10 = 0;
    }
    cVar5 = FUN_00690e60(0x78467823, inputEntityId, actionHash);  // Check second action trigger
    if (cVar5 == '\0') {
        *(undefined1 *)(thisPtr + 0x13) = 0;  // Clear toggle flag
    }
    else {
        iVar10 = 2;   // Set state to 2 (special mode)
        *(bool *)(thisPtr + 0x13) = *(char *)(thisPtr + 0x13) == '\0';  // Toggle flag
    }

    // Handle analog input (e.g., left stick) to trigger sounds based on state
    if (((*analogInput != 0.0) || (analogInput[1] != 0.0)) && (iVar6 != 0)) {
        if (iVar10 == 1) {
            if (gameMode != 2) {
                uVar9 = FUN_00798f50(0);  // Load sound for state 1
                FUN_00466880(uVar9);  // Play sound
            }
        }
        else if (iVar10 == 2) {
            uVar9 = FUN_00798f50(0);  // Load sound for state 2
            FUN_00466880(uVar9);
            if (*(char *)(thisPtr + 0x13) != '\0') {  // If toggle flag active
                FUN_00466880(0x466dc7de);  // Play additional sound (by hash)
                return;
            }
        }
    }
    return;
}