// FUNC_NAME: PlayerF2FSM::updateRightArm
void __fastcall PlayerF2FSM::updateRightArm(int thisPtr)
{
  int *pRWeaponNode;
  int iVar3;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44 [4];
  undefined4 *local_40;
  int local_3c [12];
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  pRWeaponNode = (int *)(thisPtr + 0x2190); // +0x2190: r_weaponNode
  if (*(int *)(thisPtr + 0x2190) != 0) {
    FUN_007a5240(); // releaseCurrentWeaponNode
  }
  local_48 = 0;
  local_4c = 0;
  local_50 = 0;
  // buildWeaponTransform(thisPtr, &transform, animFOV, animZoom, flag)
  FUN_008c9650(thisPtr, &local_50, *(undefined4 *)(thisPtr + 0x2038), *(undefined4 *)(thisPtr + 0x2034), 0);
  // getWeaponBoneTransform("r_weapon")
  FUN_008c9810("r_weapon");
  local_c = *(undefined4 *)(thisPtr + 0x2044); // +0x2044: weaponOffsetX
  local_8 = *(undefined4 *)(thisPtr + 0x2048); // +0x2048: weaponOffsetY
  local_4 = 1;
  iVar3 = FUN_008ca3b0(local_44); // createWeaponNode
  if (*pRWeaponNode != iVar3) {
    if (*pRWeaponNode != 0) {
      FUN_004daf90(pRWeaponNode); // deleteWeaponNode
    }
    *pRWeaponNode = iVar3;
    if (iVar3 != 0) {
      *(undefined4 *)(thisPtr + 0x2194) = *(undefined4 *)(iVar3 + 4); // +0x2194: r_weaponNodePrev
      *(int **)(iVar3 + 4) = pRWeaponNode;
    }
  }
  // checkGameState(SPECIFIC_STATE)
  iVar3 = FUN_00625050(0xc4bc3ce7, 0);
  if (iVar3 != 0) {
    FUN_007e34b0(); // handleStateChange
  }
  if (local_3c[0] != 0) {
    FUN_004daf90(local_3c); // cleanupTempNodeList
  }
  while (local_40 != (undefined4 *)0x0) {
    undefined4 *puVar2 = (undefined4 *)local_40[1];
    local_40[1] = 0;
    *local_40 = 0;
    local_40 = puVar2;
  }
  return;
}