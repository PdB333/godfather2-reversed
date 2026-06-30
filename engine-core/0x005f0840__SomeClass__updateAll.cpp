// FUNC_NAME: SomeClass::updateAll
undefined1 SomeClass::updateAll(void)

{
  int iVar1;
  char cVar2;
  undefined1 uVar3;
  int this;
  
  uVar3 = 1;
  if (*(short *)(this + 0x12) == 0) {
    return 1;
  }
  for (iVar1 = *(int *)(this + 8); iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
    cVar2 = FUN_005f03c0(this);
    if (cVar2 == '\0') {
      uVar3 = 0;
    }
  }
  return uVar3;
}