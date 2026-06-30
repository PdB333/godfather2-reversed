// FUNC_NAME: SimManager::processEntityList
void SimManager::processEntityList(int param_1, int param_2, int param_3, int param_4)
{
  bool bVar3;
  int local_68;
  int local_64;
  char cVar4;
  int iVar5;
  int iVar8;
  undefined4 *puVar10;
  undefined4 *puVar1;
  undefined4 *puVar11;
  undefined4 *puVar9;
  int local_60;
  undefined4 *local_5c;
  int local_58;
  undefined4 local_54;
  int local_50;
  undefined4 *local_4c;
  int local_48;
  undefined4 local_44;
  undefined1 *local_40;
  code *pcStack_34;
  undefined1 *local_30;
  code *pcStack_24;
  int local_20 [3];
  code *local_14;
  int local_10 [3];
  code *local_4;

  bVar3 = false;
  local_68 = 0;
  local_64 = 0;
  cVar4 = FUN_00699140(param_1, &local_68, &local_64); // getEntityRange
  if ((cVar4 != '\0') && (local_68 != local_64)) {
    local_60 = param_3;
    do {
      FUN_004d3b50(local_68 + 0x10); // lockEntity
      bVar2 = false;
      iVar8 = 0;
      do {
        iVar5 = FUN_004d4b70(*(undefined4 *)(param_2 + iVar8 * 8)); // checkComponent
        if (iVar5 == 0) {
          bVar2 = true;
          break;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < 0xc);
      iVar8 = 0;
      puVar10 = (undefined4 *)(param_2 + 0x70);
      do {
        if ((bVar2) || (iVar5 = FUN_004d4b70(*puVar10), iVar5 == 0)) goto LAB_006953b0;
        iVar8 = iVar8 + 1;
        puVar10 = puVar10 + 2;
      } while (iVar8 < 4);
      puVar7 = local_30;
      if (local_30 == (undefined1 *)0x0) {
        puVar7 = &DAT_0120546e;
      }
      if (DAT_01129d24 < 4) {
        (&DAT_01129d30)[DAT_01129d24 * 5] = 1;
        FUN_004d3d90(puVar7);
      }
      DAT_01129d24 = DAT_01129d24 + 1;
LAB_006953b0:
      FUN_004d3b50(local_68 + 0x20); // unlockEntity
      puVar7 = local_40;
      if (local_40 == (undefined1 *)0x0) {
        puVar7 = &DAT_0120546e;
      }
      FUN_004d3bc0(puVar7);
      puVar10 = *(undefined4 **)(param_3 + 4);
      cVar4 = *(char *)((int)puVar10[1] + 0x25);
      puVar1 = puVar10;
      puVar11 = (undefined4 *)puVar10[1];
      while (cVar4 == '\0') {
        iVar8 = FUN_004d4b20(local_10);
        if (iVar8 < 0) {
          puVar9 = (undefined4 *)puVar11[2];
          puVar11 = puVar1;
        }
        else {
          puVar9 = (undefined4 *)*puVar11;
        }
        puVar1 = puVar11;
        puVar11 = puVar9;
        cVar4 = *(char *)((int)puVar9 + 0x25);
      }
      local_5c = puVar1;
      if ((puVar1 == *(undefined4 **)(param_3 + 4)) || (iVar8 = FUN_004d4b20(puVar1 + 3), iVar8 < 0)
         ) {
        local_54 = *(undefined4 *)(param_3 + 4);
        local_58 = param_3;
        piVar6 = &local_58;
      }
      else {
        piVar6 = &local_60;
      }
      puVar1 = (undefined4 *)piVar6[1];
      if ((*piVar6 == 0) || (*piVar6 != param_3)) {
        FUN_00b97aea();
      }
      if (puVar1 == puVar10) {
        puVar7 = local_40;
        if (local_40 == (undefined1 *)0x0) {
          puVar7 = &DAT_0120546e;
        }
        FUN_004d3bc0(puVar7);
        puVar10 = *(undefined4 **)(param_4 + 4);
        bVar3 = true;
        cVar4 = *(char *)((int)puVar10[1] + 0x29);
        puVar1 = puVar10;
        puVar11 = (undefined4 *)puVar10[1];
        while (cVar4 == '\0') {
          iVar8 = FUN_004d4b20(local_20);
          if (iVar8 < 0) {
            puVar9 = (undefined4 *)puVar11[2];
            puVar11 = puVar1;
          }
          else {
            puVar9 = (undefined4 *)*puVar11;
          }
          puVar1 = puVar11;
          puVar11 = puVar9;
          cVar4 = *(char *)((int)puVar9 + 0x29);
        }
        local_4c = puVar1;
        local_50 = param_4;
        if ((puVar1 == *(undefined4 **)(param_4 + 4)) ||
           (iVar8 = FUN_004d4b20(puVar1 + 3), iVar8 < 0)) {
          local_44 = *(undefined4 *)(param_4 + 4);
          local_48 = param_4;
          piVar6 = &local_48;
        }
        else {
          piVar6 = &local_50;
        }
        puVar1 = (undefined4 *)piVar6[1];
        if ((*piVar6 == 0) || (*piVar6 != param_4)) {
          FUN_00b97aea();
        }
        if (puVar1 != puVar10) goto LAB_00695504;
        bVar2 = true;
      }
      else {
LAB_00695504:
        bVar2 = false;
      }
      if ((bVar3) && (bVar3 = false, local_20[0] != 0)) {
        (*local_14)(local_20[0]);
      }
      if (local_10[0] != 0) {
        (*local_4)(local_10[0]);
      }
      if (bVar2) {
        puVar7 = local_40;
        if (local_40 == (undefined1 *)0x0) {
          puVar7 = &DAT_0120546e;
        }
        if (DAT_01129d24 < 4) {
          (&DAT_01129d30)[DAT_01129d24 * 5] = 1;
          FUN_004d3d90(puVar7);
        }
        DAT_01129d24 = DAT_01129d24 + 1;
      }
      if (local_40 != (undefined1 *)0x0) {
        (*pcStack_34)(local_40);
      }
      if (local_30 != (undefined1 *)0x0) {
        (*pcStack_24)(local_30);
      }
      local_68 = FUN_00ab3c50(local_68);
    } while (local_68 != local_64);
  }
  return;
}