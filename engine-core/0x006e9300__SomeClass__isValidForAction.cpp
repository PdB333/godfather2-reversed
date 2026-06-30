// FUNC_NAME: SomeClass::isValidForAction
undefined4 __thiscall isValidForAction(int this, int actionId)
{
  int iVar1;
  
  if (*(char *)(this + 0xa8) == '\0') {
    return 0;
  }
  if ((*(int *)(this + 0x98) != 0) && (*(int *)(this + 0x98) != 0x48)) {
    if (*(int *)(this + 0x98) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(this + 0x98) + -0x48;
    }
    if (iVar1 != actionId) {
      return 0;
    }
  }
  return 1;
}