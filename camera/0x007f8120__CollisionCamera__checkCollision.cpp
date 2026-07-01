// FUNC_NAME: CollisionCamera::checkCollision
bool CollisionCamera::checkCollision(int param_1, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 != 0) {
    iVar2 = FUN_00471610();
    iVar3 = FUN_00471610();
    iVar4 = FUN_00471610();
    cVar1 = FUN_007f7f30(iVar4 + 0x30,iVar3 + 0x30,iVar2 + 0x20,param_2);
    if (cVar1 != '\0') {
      iVar2 = FUN_00471610();
      iVar3 = FUN_00471610();
      iVar4 = FUN_00471610();
      cVar1 = FUN_007f7f30(iVar4 + 0x30,iVar3 + 0x30,iVar2 + 0x20,param_2);
      if (cVar1 != '\0') {
        return 1;
      }
    }
  }
  return 0;
}