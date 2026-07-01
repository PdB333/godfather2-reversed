// FUNC_NAME: Player::handleWeaponPickup
void __thiscall Player::handleWeaponPickup(int this, undefined4 param_2)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *local_8;
  int local_4;
  
  if (*(char *)(this + 0x1a4) == '\0') {
    return;
  }
  iVar5 = 0;
  iVar4 = this + 0x88;
  local_4 = this;
  do {
    if ((*(int *)(iVar4 + 0x30) != 0) &&
       (piVar2 = (int *)FUN_00446100(iVar4,0), piVar2 != (int *)0x0)) {
      local_8 = (int *)0x0;
      cVar1 = (**(code **)(*piVar2 + 0x10))(0x254cce9,&local_8);
      if ((cVar1 != '\0') &&
         (((local_8 != (int *)0x0 && (iVar3 = (**(code **)(*local_8 + 0x160))(), iVar3 != 0)) &&
          (cVar1 = FUN_00420950(param_2), cVar1 != '\0')))) {
        FUN_008e2850(iVar3,iVar5 * 0x5c + 0x88 + this);
        return;
      }
    }
    iVar5 = iVar5 + 1;
    iVar4 = iVar4 + 0x5c;
    if (2 < iVar5) {
      return;
    }
  } while( true );
}