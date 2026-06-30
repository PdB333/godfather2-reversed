// FUNC_NAME: SomeContainer::removeEntries
undefined4 SomeContainer::removeEntries(int thisPtr, int *entries)
{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  uint *unaff_EDI;
  
  if (entries != (int *)0x0) {
    uVar5 = 0;
    piVar4 = entries;
    if (*unaff_EDI != 0) {
      do {
        iVar1 = *piVar4;
        if (iVar1 != 0) {
          piVar2 = *(int **)(iVar1 + 4);
          if (piVar2 == piVar4) {
            *(int *)(iVar1 + 4) = piVar4[1];
          }
          else {
            piVar3 = (int *)piVar2[1];
            while (piVar3 != piVar4) {
              piVar2 = (int *)piVar2[1];
              piVar3 = (int *)piVar2[1];
            }
            piVar2[1] = piVar4[1];
          }
        }
        uVar5 = uVar5 + 1;
        piVar4 = piVar4 + 3;
      } while (uVar5 < *unaff_EDI);
    }
    (**(code **)(**(int **)(thisPtr + 0x10) + 4))(entries,0);
  }
  return 0;
}