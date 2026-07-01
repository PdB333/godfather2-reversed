// FUNC_NAME: SomeClass::updateSomeState
void __thiscall SomeClass::updateSomeState(int this, int param_2)
{
  int iVar1;
  char cVar2;
  int *piVar3;
  int unaff_ESI;
  
  iVar1 = *(int *)(param_2 + 0x30);
  if ((iVar1 == 2) || (iVar1 == 4)) {
    *(undefined4 *)(this + 0x30) = DAT_0120521c;
  }
  else if ((((iVar1 == 3) || (iVar1 == 1)) && (*(int *)(param_2 + 0xc) != 0)) &&
          (*(int *)(param_2 + 0xc) != 0x48)) {
    if (*(int *)(param_2 + 0xc) == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)(*(int *)(param_2 + 0xc) + -0x48);
    }
    param_2 = 0;
    cVar2 = (**(code **)(*piVar3 + 0x10))(0x383225a1,&param_2);
    if ((cVar2 != '\\0') && (unaff_ESI != 0)) {
      *(undefined4 *)(this + 0x30) = DAT_0120521c;
      return;
    }
  }
  return;
}