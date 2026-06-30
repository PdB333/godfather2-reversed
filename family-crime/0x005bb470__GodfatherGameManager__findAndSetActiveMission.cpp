// FUNC_NAME: GodfatherGameManager::findAndSetActiveMission
undefined4 GodfatherGameManager::findAndSetActiveMission(void)

{
  byte bVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  int iVar9;
  bool bVar10;
  undefined4 local_1c;
  undefined4 local_18;
  byte *local_14;
  byte local_10 [16];
  
  cVar3 = FUN_005a8030(); // IsGameActive?
  if (cVar3 != '\0') {
    FUN_005a0d00(0); // SetMissionActive(0) - clear current
    local_14 = local_10;
    local_1c = 0;
    local_18 = 0;
    local_10[0] = 0;
    local_10[1] = 0;
    local_10[2] = 0;
    local_10[3] = 0;
    local_10[4] = 0;
    local_10[5] = 0;
    local_10[6] = 0;
    local_10[7] = 0;
    local_10[8] = 0;
    local_10[9] = 0;
    local_10[10] = 0;
    local_10[0xb] = 0;
    local_10[0xc] = 0;
    local_10[0xd] = 0;
    local_10[0xe] = 0;
    local_10[0xf] = 0;
    iVar4 = FUN_005a78b0(); // GetMissionManager()
    iVar2 = *(int *)(iVar4 + 0x4c); // +0x4c: missionList
    FUN_005a92b0(&local_1c); // GetCurrentMissionName()
    iVar9 = 0;
    if (0 < *(int *)(iVar2 + 0x30)) { // +0x30: missionCount
      puVar8 = *(undefined4 **)(iVar2 + 0x34); // +0x34: missionArray (pairs of name+data)
      do {
        pbVar7 = (byte *)*puVar8; // mission name string
        pbVar5 = local_14; // current mission name
        do {
          bVar1 = *pbVar5;
          bVar10 = bVar1 < *pbVar7;
          if (bVar1 != *pbVar7) {
LAB_005bb510:
            iVar6 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
            goto LAB_005bb515;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar5[1];
          bVar10 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_005bb510;
          pbVar5 = pbVar5 + 2;
          pbVar7 = pbVar7 + 2;
        } while (bVar1 != 0);
        iVar6 = 0;
LAB_005bb515:
        if (iVar6 == 0) { // name match
          if (**(int **)(*(int *)(iVar2 + 0x18) + // +0x18: missionDataTable
                        *(int *)(*(int *)(iVar2 + 0x34) + 4 + iVar9 * 8) * 4) == 6) { // mission type check (6 = main story?)
            *(undefined4 *)(iVar4 + 0x50) = // +0x50: activeMissionData
                 *(undefined4 *)
                  (*(int *)(*(int *)(iVar2 + 0x18) +
                           *(int *)(*(int *)(iVar2 + 0x34) + 4 + iVar9 * 8) * 4) + 8);
            *(undefined4 *)(iVar4 + 0x54) = *(undefined4 *)(*(int *)(iVar2 + 0x34) + iVar9 * 8); // +0x54: activeMissionName
          }
          break;
        }
        iVar9 = iVar9 + 1;
        puVar8 = puVar8 + 2;
      } while (iVar9 < *(int *)(iVar2 + 0x30));
    }
    if ((local_14 != local_10) && (local_14 != (byte *)0x0)) {
      (*DAT_0119caf4)(local_14); // free allocated string
    }
  }
  return DAT_0119cbbc; // some global state
}