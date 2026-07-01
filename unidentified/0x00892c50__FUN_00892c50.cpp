// FUNC_NAME: SomeClass::updateSomething
void __thiscall SomeClass::updateSomething(int this, undefined4 param_2, int param_3, int param_4)
{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  
  FUN_00892b40(param_2, param_4);
  *(undefined4 *)(this + 8) = *(undefined4 *)(param_3 + 0x30);
  if ((((*(byte *)(this + 0x10) & 1) == 0) && (*(int *)(param_3 + 0xc) != 0)) &&
     (*(int *)(param_3 + 0xc) != 0x48)) {
    if (*(int *)(param_3 + 0xc) == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(*(int *)(param_3 + 0xc) + -0x48);
    }
    param_4 = 0;
    cVar1 = (**(code **)(*piVar3 + 0x10))(0x383225a1, &param_4);
    if ((cVar1 != '\0') && (param_4 != 0)) {
      *(byte *)(this + 0x10) = *(byte *)(this + 0x10) | 1;
    }
  }
  uVar2 = FUN_0084dba0(param_2);
  *(undefined4 *)(this + 4) = uVar2;
  return;
}