// FUNC_NAME: PlayerSM::updateCombatState
void __fastcall PlayerSM::updateCombatState(int this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar1 = *(int *)(this + 0x20);  // +0x20: pointer to player list
  iVar3 = 0;
  if (0 < *(int *)(iVar1 + 0xc)) {  // +0x0c: count of players
    do {
      iVar1 = *(int *)(*(int *)(iVar1 + 8) + iVar3 * 4);  // +0x08: player array
      bVar4 = *(char *)(iVar1 + 0xd8) != '\x06';  // +0xd8: combat state enum (6 = in combat)
      iVar2 = FUN_009f4440();  // check if player is in combat
      if ((iVar2 != 0) || (bVar4)) {
        FUN_009f4240(1,1,0);  // set combat state
        *(undefined2 *)(iVar1 + 0x2a) = 5;  // +0x2a: combat timer
        if ((!bVar4) && (*(int *)(iVar1 + 8) != 0)) {  // +0x08: weapon pointer
          FUN_009e9e90(iVar1,1,0);  // equip weapon
        }
      }
      iVar1 = *(int *)(this + 0x20);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(iVar1 + 0xc));
  }
  return;
}