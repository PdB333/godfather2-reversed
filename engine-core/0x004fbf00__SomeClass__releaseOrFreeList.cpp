// FUNC_NAME: SomeClass::releaseOrFreeList
void SomeClass::releaseOrFreeList(void)
{
  int *pItem;
  int *piVar2;
  int *pListHead;
  
  if (*unaff_EDI != 0) {
    // Call some cleanup function (likely destructor or release)
    FUN_004fc520();
    
    pItem = (int *)*unaff_EDI;
    piVar2 = (int *)(DAT_01206880 + 0x14);  // +0x14: free list head pointer offset in global manager
    
    // Set the vtable pointer (or type marker) for the item being freed
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01123be8;
    
    // Add the item to the free list (linked list insertion at head)
    *piVar2 = *piVar2 + 4;
    *(int *)*piVar2 = (int)pItem;
    *piVar2 = *piVar2 + 4;
    
    // Clear the original pointer and its next pointer
    *unaff_EDI = 0;
    unaff_EDI[1] = 0;
  }
  return;
}