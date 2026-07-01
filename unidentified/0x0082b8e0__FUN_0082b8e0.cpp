// FUNC_NAME: SomeContainer::findByFourInts
int __thiscall SomeContainer::findByFourInts(int this, int *param_2)
{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (*(uint *)(this + 0xc) != 0) {
    piVar2 = *(int **)(this + 8);
    do {
      iVar1 = *piVar2;
      if ((((*(int *)(iVar1 + 0x1c) == *param_2) && (*(int *)(iVar1 + 0x20) == param_2[1])) &&
          (*(int *)(iVar1 + 0x24) == param_2[2])) && (*(int *)(iVar1 + 0x28) == param_2[3])) {
        return iVar1;
      }
      uVar3 = uVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (uVar3 < *(uint *)(this + 0xc));
  }
  return 0;
}