// Xbox PDB: EARS_Apt_UIFamilyMemberInfo_SetHonorSummary
// FUNC_NAME: PlayerReputationTracker::sendHonorSummary
void __fastcall PlayerReputationTracker::sendHonorSummary(int this)
{
    byte bVar1;
    int iVar2;
    char *pcVar3;
    char *pcVar4;
    int iVar5;
    char *local_30;
    undefined4 local_2c;
    undefined4 local_28;
    code *local_24;
    char *local_20;
    undefined4 local_1c;
    undefined4 local_18;
    code *local_14;
    char *local_10;
    undefined4 local_c;
    undefined4 local_8;
    code *local_4;

    // Check if honor summary has already been sent (flag at +0x50)
    if (*(int *)(this + 0x50) == 0) {
        iVar2 = FUN_0090a5a0(); // Get player data
        bVar1 = FUN_008bcf60(iVar2 + 0x20); // Get honor level (0-3)
        if (bVar1 < 4) {
            local_10 = (char *)0x0;
            local_c = 0;
            local_8 = 0;
            local_4 = (code *)0x0;
            local_20 = (char *)0x0;
            local_1c = 0;
            local_18 = 0;
            local_14 = (code *)0x0;
            iVar2 = FUN_008bcf00(iVar2 + 0x20); // Get honor points
            FUN_00603d30(iVar2, &local_10, 1); // Format honor points as string
            if (bVar1 == 1) {
                iVar5 = 10; // Honor level 1 -> 10 points
            }
            else {
                iVar5 = (-(uint)(bVar1 != 2) & 0x2d) + 0x19; // Level 2 -> 25, Level 3 -> 40
            }
            FUN_00603d30(iVar5 - iVar2, &local_20, 1); // Format remaining points to next level
            local_30 = (char *)0x0;
            local_2c = 0;
            local_28 = 0;
            local_24 = (code *)0x0;
            pcVar3 = local_20;
            if (local_20 == (char *)0x0) {
                pcVar3 = &DAT_0120546e; // Empty string placeholder
            }
            pcVar4 = local_10;
            if (local_10 == (char *)0x0) {
                pcVar4 = &DAT_0120546e; // Empty string placeholder
            }
            FUN_004d4ad0(&local_30, "{x:%s}{y:%s}{$pause_upgrades_honors_earned}", pcVar4, pcVar3);
            pcVar3 = local_30;
            if (local_30 == (char *)0x0) {
                pcVar3 = &DAT_0120546e; // Empty string placeholder
            }
            FUN_005a04a0("SetHonorSummary", 0, &DAT_00d88708, 1, pcVar3); // Send to UI
            if (local_30 != (char *)0x0) {
                (*local_24)(local_30); // Free string
            }
            if (local_20 != (char *)0x0) {
                (*local_14)(local_20); // Free string
            }
            if (local_10 != (char *)0x0) {
                (*local_4)(local_10); // Free string
            }
        }
    }
    return;
}