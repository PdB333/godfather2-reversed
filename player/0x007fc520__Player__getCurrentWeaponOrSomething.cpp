// FUNC_NAME: Player::getCurrentWeaponOrSomething
undefined4 __thiscall Player::getCurrentWeaponOrSomething(undefined8 *this, undefined8 *outParam)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined8 *local_4;
  
  // Check if weapon slot is empty (0) or invalid (0x48)
  if ((*(int *)(this + 0x38f) == 0) || (*(int *)(this + 0x38f) == 0x48)) {
    if (*(int *)(this + 0x38f) == 0) {
      return 0;
    }
    if (*(int *)(this + 0x38f) == 0x48) {
      return 0;
    }
    local_4 = this;
    iVar3 = FUN_00471610();  // Get some global data
    *outParam = *(undefined8 *)(iVar3 + 0x30);
    *(undefined4 *)(outParam + 1) = *(undefined4 *)(iVar3 + 0x38);
  }
  else {
    if (*(int *)(this + 0x38f) == 0) {
      piVar2 = (int *)0x0;
    }
    else {
      piVar2 = (int *)(*(int *)(this + 0x38f) + -0x48);
    }
    iVar3 = 0x55859efa;
    local_4 = (undefined8 *)0x0;
    cVar1 = (**(code **)(*piVar2 + 0x10))(0x55859efa, &local_4);
    if ((cVar1 != '\0') && (iVar3 != 0)) {
      *local_4 = *(undefined8 *)(iVar3 + 0x1b80);
      *(undefined4 *)(local_4 + 1) = *(undefined4 *)(iVar3 + 0x1b88);
      return 1;
    }
  }
  return 1;
}