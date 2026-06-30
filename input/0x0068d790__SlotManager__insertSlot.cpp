// FUNC_NAME: SlotManager::insertSlot
uint SlotManager::insertSlot(int param_1, int *param_2, undefined8 *param_3)
{
  undefined8 *puVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint local_8;
  uint local_4;
  
  if (*(int *)(param_3 + 3) == 2) {
    // Forward search (type == 2)
    local_4 = 0xffffffff;
    local_8 = 0xffffffff;
    uVar7 = 0xffffffff;
    if (*(uint *)((int)param_3 + 0x1c) != 0) {
      uVar5 = 0;
      pcVar6 = (char *)(param_1 + 0x20); // +0x20: slot array start
      uVar8 = 0;
      do {
        uVar7 = 0;
        if (uVar5 < uVar5 + 3) {
          iVar2 = (uVar5 + 3) - uVar5;
          pcVar3 = pcVar6;
          do {
            if (*pcVar3 != '\0') {
              uVar7 = uVar7 + 1;
            }
            pcVar3 = pcVar3 + 0x24; // +0x24: slot size
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        if ((uVar7 < local_8) && (uVar7 < 3)) {
          local_8 = uVar7;
          local_4 = uVar8;
        }
        uVar8 = uVar8 + 1;
        uVar5 = uVar5 + 3;
        pcVar6 = pcVar6 + 0x6c; // +0x6c: stride between groups
        uVar7 = local_4;
      } while (uVar8 < *(uint *)((int)param_3 + 0x1c));
    }
    uVar5 = -(uint)(uVar7 != 0xffffffff) & uVar7;
  }
  else {
    // Backward search (type != 2)
    uVar7 = *(uint *)((int)param_3 + 0x1c);
    uVar8 = 0xffffffff;
    local_4 = 0xffffffff;
    uVar5 = uVar7;
    if (uVar7 != 0xffffffff) {
      uVar5 = uVar7 * 3;
      pcVar6 = (char *)(uVar7 * 0x6c + 0x8c + param_1); // +0x8c: end of slot array
      uVar4 = uVar7;
      do {
        uVar9 = 0;
        if (uVar5 < uVar5 + 3) {
          iVar2 = (uVar5 + 3) - uVar5;
          pcVar3 = pcVar6;
          do {
            if (*pcVar3 != '\0') {
              uVar9 = uVar9 + 1;
            }
            pcVar3 = pcVar3 + -0x24;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
        if ((uVar9 < uVar8) && (uVar9 < 3)) {
          uVar8 = uVar9;
          local_4 = uVar4;
        }
        uVar4 = uVar4 - 1;
        uVar5 = uVar5 - 3;
        pcVar6 = pcVar6 + -0x6c;
      } while (uVar4 != 0xffffffff);
      uVar5 = local_4;
      if (local_4 == 0xffffffff) {
        uVar5 = uVar7;
      }
    }
  }
  if ((uint)(*param_2 * 3) <= uVar5) {
    return 0xffffffff;
  }
  puVar1 = (undefined8 *)(param_1 + uVar5 * 0x24);
  *puVar1 = *param_3;
  puVar1[1] = param_3[1];
  puVar1[2] = param_3[2];
  puVar1[3] = param_3[3];
  *(undefined4 *)(puVar1 + 4) = *(undefined4 *)(param_3 + 4);
  return uVar5;
}