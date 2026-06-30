// FUNC_NAME: SomeContainer::removeElementsFromFront
void SomeContainer::removeElementsFromFront(int param_1)
{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int unaff_ESI;
  int unaff_EDI;
  
  // Adjust the start pointer by removing unaff_EDI elements from the front (each element is 8 bytes)
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + unaff_EDI * -8;
  iVar3 = 0;
  if (0 < unaff_EDI) {
    do {
      iVar1 = *(int *)(param_1 + 8);
      puVar2 = *(undefined4 **)(unaff_ESI + 8);
      *puVar2 = *(undefined4 *)(iVar1 + iVar3 * 8);
      puVar2[1] = *(undefined4 *)(iVar1 + iVar3 * 8 + 4);
      *(int *)(unaff_ESI + 8) = *(int *)(unaff_ESI + 8) + 8;
      iVar3 = iVar3 + 1;
    } while (iVar3 < unaff_EDI);
  }
  return;
}