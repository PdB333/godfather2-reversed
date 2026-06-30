// FUNC_NAME: GodfatherGameManager::updateGameState
void GodfatherGameManager::updateGameState(int param_1)
{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int unaff_FS_OFFSET;
  undefined4 uVar6;
  uint local_90;
  undefined4 local_88;
  
  local_90 = (uint)*(ushort *)(param_1 + 0x30); // +0x30: some counter/state
  if ((((local_90 != 0) && (*(int *)(param_1 + 0x5c) != 0)) &&
      (DAT_00e2af44 < *(float *)(param_1 + 0x40))) &&
     (DAT_00e2af44 < *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x2c))) {
    iVar4 = **(int **)(unaff_FS_OFFSET + 0x2c);
    if (((*(uint *)(*(int *)(param_1 + 8) + *(int *)(iVar4 + 8)) & 0x200) == 0) ||
       (*(int *)(DAT_012234c4 + 0x24) == 0)) {
      local_88 = 0;
    }
    else {
      local_88 = 1;
    }
    FUN_00537670(); // some initialization
    FUN_00537610(); // some initialization
    if ((*(byte *)(*(int *)(param_1 + 0x10) + 0x104) & 4) != 0) {
      FUN_00417560(); // handle some flag
      FUN_00537b40(DAT_01163840 != '\0'); // some boolean parameter
      FUN_005378e0(); // some update
      FUN_00537880(); // some update
    }
    iVar3 = *(int *)(param_1 + 0x10);
    if (*(char *)(iVar3 + 0x60) == '\x01') {
      FUN_00537790(*(undefined4 *)(param_1 + 0x60)); // +0x60: some parameter
      iVar3 = *(int *)(param_1 + 0x10);
    }
    if ((*(uint *)(iVar3 + 0x104) & 0x100) != 0) {
      FUN_005121b0(); // handle some flag
    }
    if (*(int *)(param_1 + 0x58) != 0) {
      FUN_005120c0(); // handle some state
    }
    if ((*(byte *)(*(int *)(param_1 + 0x10) + 0x104) & 0x40) != 0) {
      FUN_00b9c041(); // handle some flag
    }
    FUN_00537a70(); // some update
    FUN_00537750(*(undefined4 *)(param_1 + 0x5c)); // +0x5c: some parameter
    FUN_00412f50(~*(byte *)(*(int *)(param_1 + 0x10) + 0x10c) & 1); // some flag
    FUN_00412f10(*(uint *)(*(int *)(param_1 + 0x10) + 0x108) >> 0x1c & 0xffffff01); // some flag
    if (DAT_012058d0 < 0x16) {
      DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
      DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1;
    FUN_00417fe0(1); // set some state
    FUN_004ec7a0(); // some update
    cVar1 = *(char *)(*(int *)(param_1 + 0x10) + 0x112);
    uVar6 = DAT_00e2b1a4;
    if ((cVar1 != '\0') && (cVar1 != '\x02')) {
      uVar6 = 0;
    }
    FUN_00537d80(local_88,uVar6,1,*(uint *)(*(int *)(param_1 + 0x10) + 0x10c) >> 0x1b & 0xffffff01); // some update with parameters
    bVar2 = *(byte *)(*(int *)(param_1 + 0x10) + 0x171);
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
    _DAT_011f3a38 = (uint)bVar2;
    if (DAT_012058d0 < 0xf) {
      DAT_012058d0 = 0xf;
    }
    if (0xf < DAT_00f15988) {
      DAT_00f15988 = 0xf;
    }
    _DAT_011f3a14 = (uint)(bVar2 != 0);
    if ((*(byte *)(*(int *)(param_1 + 8) + *(int *)(iVar4 + 8)) & 4) != 0) {
      FUN_00417560(); // handle some flag
    }
    FUN_00537ad0(); // some update
    FUN_00537b20(); // some update
    FUN_00537a90(); // some update
    FUN_00537ab0(); // some update
    uVar5 = *(uint *)(*(int *)(param_1 + 0x10) + 0x104);
    FUN_00537640(); // some update
    iVar4 = FUN_0060cd00(0xd,(-((uVar5 & 0x1000) != 0) & 4U) + 4,0x80000000,local_90,1); // some allocation/creation
    if (iVar4 != 0) {
      uVar5 = (uint)*(ushort *)(param_1 + 0x32);
      do {
        local_90 = local_90 - 1;
        FUN_00512010(); // some per-item update
        uVar5 = uVar5 + 1;
        if ((int)*(short *)(param_1 + 0x6e) <= (int)uVar5) {
          uVar5 = uVar5 - (int)*(short *)(param_1 + 0x6e);
        }
      } while (local_90 != 0);
      FUN_0060cde0(); // some cleanup
      FUN_00537230(); // some update
    }
    FUN_00537750(0); // reset some parameter
    if (*(uint *)(DAT_0121b0ac + 4) != 0) {
      uVar5 = *(uint *)(DAT_0121b0ac + 4) & 0xff;
      if ((&DAT_011eb8fc)[DAT_0121a394 * 0x10] != '\0') {
        uVar5 = uVar5 + 0x10;
      }
      FUN_00618d40(); // some update
      (&DAT_011d912c)[uVar5] = 0;
    }
    if ((*(uint *)(*(int *)(param_1 + 0x10) + 0x104) & 0x100) != 0) {
      FUN_00537990(0); // handle some flag
    }
    if (*(int *)(param_1 + 0x58) != 0) {
      FUN_005379d0(0,0); // handle some state
    }
    DAT_012058e8 = 0;
    DAT_0121a390 = 0;
    DAT_0121a394 = 0;
    FUN_00417fe0(0); // reset some state
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
    FUN_00417cf0(1,5,6); // some cleanup
    FUN_00412f50(1); // reset some flag
    FUN_00412f10(1); // reset some flag
    if (DAT_012058d0 < 0x16) {
      DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
      DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1;
  }
  return;
}