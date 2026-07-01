// FUNC_NAME: GodfatherGameManager::checkRestriction
undefined4 __thiscall GodfatherGameManager::checkRestriction(int this, char param_2)
{
  undefined4 uVar1;
  char cVar2;
  
  uVar1 = _DAT_00d5c458;
  if (*(int *)(this + 0x138) < 1) {
    if (param_2 != '\0') {
      *(undefined4 *)(this + 0x158) = 4;
      FUN_0040c2c0(0xff000000, uVar1, 0, 2);
      return 0;
    }
    if ((((*(int *)(this + 0x158) == 4) && (*(char *)(DAT_01223394 + 0x54) != '\0')) &&
        (*(int *)(DAT_01223394 + 0x58) == 1)) && (cVar2 = FUN_007dbef0(), cVar2 == '\0')) {
      return 0;
    }
    *(undefined4 *)(this + 0x158) = 0;
  }
  return 1;
}