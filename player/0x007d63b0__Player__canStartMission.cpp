// FUNC_NAME: Player::canStartMission
undefined4 __fastcall Player::canStartMission(int this)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (_DAT_00d577a0 < *(float *)(this + 0x30)) {
    uVar2 = FUN_00798f50(0x35); // Get player's current mission
    cVar1 = FUN_0079e920(uVar2); // Check if mission is active
    if (((cVar1 != '\0') && (cVar1 = FUN_007ab420(4), cVar1 != '\0')) && // Check if player is in free roam state
       (iVar3 = FUN_007ab320(), iVar3 != 0)) { // Check if player is not in combat
      return 1;
    }
  }
  return 0;
}