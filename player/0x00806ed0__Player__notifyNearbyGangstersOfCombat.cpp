// FUNC_NAME: Player::notifyNearbyGangstersOfCombat
void __thiscall Player::notifyNearbyGangstersOfCombat(int this, undefined4 param_2, undefined4 param_3, int param_4)
{
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  // Get the NPC manager from the player object (+0x1ed4)
  uVar2 = FUN_008c7530(*(undefined4 *)(this + 0x1ed4));
  // Get the list of nearby gangsters
  puVar3 = (undefined4 *)FUN_0043c2c0(uVar2);
  local_4 = 0;
  local_c = DAT_0112ad8c;
  local_8 = param_2;
  // Iterate through the linked list of gangsters
  for (piVar1 = (int *)*puVar3; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[1]) {
    iVar4 = *piVar1;
    if (iVar4 != param_4) {
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = iVar4 + 0x3c;
      }
      // Notify each gangster of combat (FUN_00408bf0 likely sets combat state)
      FUN_00408bf0(&local_c,iVar4,0);
    }
  }
  return;
}