// FUNC_NAME: SomeManager::deleteAllItems
void SomeManager::deleteAllItems(void)
{
  int *piVar3;
  int iVar2;
  int iVar4;
  int unaff_EDI; // this pointer (likely SomeManager*)
  
  iVar4 = 0;
  while( true ) {
    if ((unaff_EDI == 0) || (iVar4 < 0)) {
      return;
    }
    // +0x124: pointer to first item in a linked list or array
    piVar3 = *(int **)(unaff_EDI + 0x124);
    iVar2 = 0;
    if (0 < iVar4) {
      do {
        // +0x49*4 = +0x124: next item pointer offset
        piVar3 = (int *)piVar3[0x49];
        if (piVar3 == (int *)0x0) {
          return;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < iVar4);
    }
    if (piVar3 == (int *)0x0) break;
    // vtable at *piVar3, +4 is destructor offset
    pcVar1 = *(code **)(*piVar3 + 4);
    // +0x44*4 = +0x110: some flag or reference count
    piVar3[0x44] = 0;
    // +0x121: another flag (byte)
    *(undefined1 *)((int)piVar3 + 0x121) = 0;
    // Call destructor with -1 (delete)
    (*pcVar1)(piVar3,0xffffffff);
    iVar4 = iVar4 + 1;
  }
  return;
}