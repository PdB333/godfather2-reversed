// FUNC_NAME: SomeAllocator::findFreeAndReturn
undefined4 FUN_0051eba0(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int unaff_EDI;
  float fVar4;
  float fVar5;
  
  iVar2 = *(int *)(unaff_EDI + 4);  // +0x4: current node in freelist/linked list
  iVar3 = 0;
  if (iVar2 != *(int *)(unaff_EDI + 0xc)) {  // +0xC: end sentinel
    fVar5 = DAT_00e2eff4;  // likely a constant like 0.0f or very high
    do {
      fVar4 = DAT_00e2eff4;
      if (*(int *)(iVar2 + 0x14) != *(int *)(iVar2 + 0x1c)) {  // node has children/buffer
        fVar4 = *(float *)(*(int *)(iVar2 + 0x14) + 0x14);  // +0x14: priority/size field (float)
      }
      if (fVar5 < fVar4) {
        iVar3 = iVar2;
        fVar5 = fVar4;
      }
      iVar2 = *(int *)(iVar2 + 0x2c);  // +0x2C: next node pointer
    } while (iVar2 != *(int *)(unaff_EDI + 0xc));
    if (((iVar3 != 0) && (piVar1 = *(int **)(iVar3 + 0x14), piVar1 != *(int **)(iVar3 + 0x1c))) &&
       (piVar1 != param_1)) {
      // Remove piVar1 from its current list by patching prev/next
      *(int *)(piVar1[0x11] + 0x40) = piVar1[0x10];  // next->prev = prev
      *(int *)(piVar1[0x10] + 0x44) = piVar1[0x11];  // prev->next = next
      // Call destructor or release on piVar1
      (**(code **)(*piVar1 + 4))();  // vtable+4 = dtor/release
      // Insert piVar1 into the free list at +0x474
      piVar1[0x10] = *(int *)(unaff_EDI + 0x474);  // prev of piVar1 = old head
      *(int **)(unaff_EDI + 0x474) = piVar1;  // head = piVar1
      return 1;
    }
  }
  return 0;
}