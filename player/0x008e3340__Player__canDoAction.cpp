// FUNC_NAME: Player::canDoAction
bool __fastcall Player::canDoAction(int thisPtr)
{
  char cVar1;
  int iVar2;

  if (*(char *)(thisPtr + 0x1a5) == '\0') {
    return false;
  }
  if (*(int *)(thisPtr + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(thisPtr + 0xcc) + -0x48;
  }
  if (*(char *)(thisPtr + 0x1a4) == '\0') {
    if ((((*(int *)(thisPtr + 0xc4) != 0) && (*(int *)(thisPtr + 0xc4) != 0x48)) && (iVar2 != 0)) &&
       (cVar1 = FUN_007f47a0(), cVar1 == '\0')) {
      iVar2 = FUN_0077dd80();
      if (((2 < iVar2) && (cVar1 = FUN_00690150(0x30), cVar1 == '\0')) &&
         ((*(uint *)(thisPtr + 0x84) >> 1 & 1) == 0)) {
        return false;
      }
      return true;
    }
    return false;
  }
  return true;
}