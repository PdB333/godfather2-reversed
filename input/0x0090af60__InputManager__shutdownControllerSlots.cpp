// FUNC_NAME: InputManager::shutdownControllerSlots
void __fastcall InputManager::shutdownControllerSlots(undefined4 *this)
{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  undefined4 *puVar5;
  
  puVar1 = this + 4;
  *this = &PTR_FUN_00d833a8;
  this[3] = &PTR_LAB_00d833a4;
  *puVar1 = &PTR_LAB_00d8338c;
  puVar4 = this + 6;
  iVar3 = 7;
  do {
    if ((*puVar4 >> 1 & 1) != 0) {
      iVar2 = FUN_0090a5a0();
      if (iVar2 != 0) {
        puVar5 = puVar1;
        FUN_0090a5a0(puVar1);
        FUN_00791350(puVar5);
      }
    }
    puVar4 = puVar4 + 9;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  FUN_004086d0(&DAT_0112ff88);
  FUN_004086d0(&DAT_0112ffb4);
  FUN_004086d0(&DAT_0112ffbc);
  FUN_004086d0(&DAT_0112ffa4);
  FUN_004086d0(&DAT_0112ffc4);
  FUN_004086d0(&DAT_0112ffac);
  FUN_004086d0(&DAT_0112ff94);
  FUN_004086d0(&DAT_0112ff9c);
  FUN_00408310(&DAT_0112ff88);
  FUN_00408310(&DAT_0112ffb4);
  FUN_00408310(&DAT_0112ffbc);
  FUN_00408310(&DAT_0112ffa4);
  FUN_00408310(&DAT_0112ffc4);
  FUN_00408310(&DAT_0112ffac);
  FUN_00408310(&DAT_0112ff94);
  FUN_00408310(&DAT_0112ff9c);
  iVar3 = 6;
  do {
    FUN_0090a430();
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  this[3] = &PTR_LAB_00d832e8;
  DAT_0112989c = 0;
  FUN_004083d0();
  return;
}