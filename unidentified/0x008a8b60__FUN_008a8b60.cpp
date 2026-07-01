// FUNC_NAME: SomeClass::allocateAndInitObject
int SomeClass::allocateAndInitObject(int param_1, int param_2)
{
  char cVar1;
  int iVar2;
  int uVar3;
  int *piVar4;
  int local_4;
  
  iVar2 = FUN_00446290(param_1);
  if (iVar2 != 0) {
    piVar4 = &local_4;
    local_4 = 0;
    uVar3 = FUN_0043ab10(piVar4);
    cVar1 = FUN_008b0830(uVar3,piVar4);
    if (cVar1 != '\0') {
      // +0x18: some field in the object
      *(int *)(local_4 + 0x18) = param_2;
      FUN_00481530();
      if (local_4 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = local_4 + 0x50;
      }
      // +0x0c: some field in the object (offset from iVar2)
      *(int *)(iVar2 + 0xc) = DAT_0120540c;
      DAT_0120540c = 0;
      if (local_4 != 0) {
        return local_4 + 0x50;
      }
      return 0;
    }
  }
  return 0;
}