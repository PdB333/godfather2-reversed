// FUNC_NAME: SomeContainer::findNthOverlappingRange
int __thiscall SomeContainer::findNthOverlappingRange(int this, int param_2)
{
  int iVar1;
  int *piVar2;
  int unaff_ESI;
  
  iVar1 = 0;
  if (0 < *(int *)(this + 0x38)) {
    piVar2 = (int *)(*(int *)(this + 0x18) + 8);
    do {
      if (unaff_ESI < piVar2[-1]) {
        return 0;
      }
      if ((unaff_ESI < *piVar2) && (param_2 = param_2 + -1, param_2 == 0)) {
        return *(int *)(*(int *)(this + 0x18) + iVar1 * 0xc) + 0x10;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 3;
    } while (iVar1 < *(int *)(this + 0x38));
  }
  return 0;
}