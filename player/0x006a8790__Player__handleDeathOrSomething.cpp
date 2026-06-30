// FUNC_NAME: Player::handleDeathOrSomething
void Player::handleDeathOrSomething(int *param_1)
{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  if (((iVar1 != 0) && (iVar2 = param_1[2], iVar2 != 0)) &&
     (*(byte *)(iVar2 + 0x21) = *(byte *)(iVar2 + 0x21) & 0xfb, (*(byte *)(iVar2 + 0x21) & 2) != 0))
  {
    FUN_006a8100(iVar1,iVar2,0,0,0);
    iVar1 = **(int **)(DAT_012233a0 + 4);
    if ((iVar1 != 0) && (iVar1 != 0x1f30)) {
      FUN_00408c70(&DAT_0112b914,iVar1 + -0x1ef4,0);
    }
  }
  return;
}