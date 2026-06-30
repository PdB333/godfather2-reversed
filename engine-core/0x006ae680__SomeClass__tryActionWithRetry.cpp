// FUNC_NAME: SomeClass::tryActionWithRetry
undefined1 __thiscall SomeClass::tryActionWithRetry(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4)
{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar2 = 0;
  // +0x19c: maxRetryCount (uint)
  if (*(int *)(this + 0x19c) != 0) {
    while (cVar1 = FUN_006b7ea0(param_2, param_3, param_4), cVar1 == '\0') {
      uVar3 = uVar3 + 1;
      if (*(uint *)(this + 0x19c) <= uVar3) {
        return 0;
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}