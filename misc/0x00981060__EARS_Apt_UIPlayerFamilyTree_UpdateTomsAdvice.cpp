// Xbox PDB: EARS_Apt_UIPlayerFamilyTree_UpdateTomsAdvice
// FUNC_NAME: GodfatherGameManager::updateTomsAdvice
void __fastcall GodfatherGameManager::updateTomsAdvice(int this)
{
    uint *puVar1;
    int iVar2;
    undefined1 *puVar3;
    int iVar4;
    undefined4 local_20;
    int local_1c;
    int local_18;
    undefined4 local_14;
    undefined1 *local_10;
    undefined4 local_c;
    undefined4 local_8;
    code *local_4;

    // Check if we're past the tutorial stage (stage > 5 at +0x68)
    if (5 < *(int *)(this + 0x68)) {
        local_1c = 0;
        local_18 = 0;
        local_14 = 0;
        iVar4 = 0;
        do {
            // Iterate through 7 player slots (0xFC / 0x24 = 7)
            puVar1 = (uint *)(iVar4 + 0x18 + DAT_0112989c);
            if ((puVar1 != (uint *)0x0) && ((*puVar1 >> 2 & 1) != 0)) {
                iVar2 = FUN_0090a5a0(); // Probably isPlayerLocal or similar
                if (iVar2 != 0) {
                    local_20 = FUN_0090a5a0(); // Get some player data
                    FUN_006b44a0(&local_20);   // Convert or process it
                }
            }
            iVar4 = iVar4 + 0x24; // 0x24 bytes per player slot
        } while (iVar4 < 0xfc);   // 7 slots

        if (local_18 == 0) {
            // Hide the tom's advice UI if no advice to show
            FUN_005a04a0("HideTomsAdvice", 0, &DAT_00d8fe44, 0);
        }
        else {
            iVar2 = *(int *)(this + 100);      // +0x64 - current advice type/phase
            iVar4 = 0;
            if ((iVar2 == 1) && (*(int *)(*(int *)(this + 0x134) + 0xfc) != 0)) {
                iVar4 = 4; // Type 4 advice
            }
            else if (iVar2 == 2) {
                iVar4 = 1; // Type 1 advice
            }
            else if (iVar2 == 3) {
                iVar4 = 2; // Type 2 advice
            }
            local_10 = (undefined1 *)0x0;
            local_c = 0;
            local_8 = 0;
            local_4 = (code *)0x0;
            iVar2 = FUN_008c74d0(0x637b907); // Check some resource/flag
            if ((iVar2 != 0) && (iVar4 != 0)) {
                // Get the advice string based on context
                FUN_008c62b0(&local_10, &local_1c, *(undefined4 *)(this + 0x134), iVar4);
                puVar3 = local_10;
                if (local_10 == (undefined1 *)0x0) {
                    puVar3 = &DAT_0120546e; // Empty string fallback
                }
                FUN_005a04a0("ShowTomsAdvice", 0, &DAT_00d8fe44, 1, puVar3);
            }
            if (local_10 != (undefined1 *)0x0) {
                (*local_4)(local_10); // Free the string
            }
        }
        if (local_1c != 0) {
            FUN_009c8f10(local_1c); // Cleanup
        }
    }
}