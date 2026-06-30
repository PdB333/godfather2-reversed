// FUNC_NAME: UnknownClass::clearRefCountList
void FUN_0054a570(void)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *unaff_EDI; // this pointer
  
  iVar3 = 0;
  *unaff_EDI = &PTR_LAB_00e39c3c; // vtable setup, +0x00
  if (0 < (int)unaff_EDI[4]) { // +0x10: refCountListSize
    do {
      iVar1 = *(int *)(unaff_EDI[3] + iVar3 * 4); // +0x0C: refCountList, array of pointers
      if (iVar1 != 0) {
        if (*(int *)(iVar1 + 0x40) != 0) { // object +0x40: some ref counted sub-object
          FUN_00557020();
          puVar2 = *(undefined4 **)(iVar1 + 0x40);
          if ((*(short *)(puVar2 + 1) != 0) && // sub-object ref count (2 bytes at +4)
             (*(short *)((int)puVar2 + 6) = *(short *)((int)puVar2 + 6) + -1, // decrement ref count
             *(short *)((int)puVar2 + 6) == 0)) {
            (**(code **)*puVar2)(1); // call virtual destructor with 1 (delete)
          }
          *(undefined4 *)(iVar1 + 0x40) = 0; // clear pointer
        }
        FUN_009c8eb0(iVar1); // release/delete object
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)unaff_EDI[4]);
  }
  unaff_EDI[4] = 0; // size = 0
  FUN_009c8f10(unaff_EDI[3]); // free list array memory
  unaff_EDI[3] = 0; // clear list pointer
  unaff_EDI[5] = 0; // +0x14: some capacity field
  (**(code **)(*(int *)unaff_EDI[2] + 0xc))(); // call virtual function at vtable+0x0C (likely destructor chain)
  if (unaff_EDI[3] != 0) { // safety check
    FUN_009c8f10(unaff_EDI[3]);
  }
  FUN_0049c640(); // likely global cleanup function
  return;
}