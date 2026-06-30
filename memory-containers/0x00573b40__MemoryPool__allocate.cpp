// FUNC_NAME: MemoryPool::allocate
void MemoryPool::allocate(void)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int unaff_ESI;  // this pointer
  
  // Check if free list is empty
  piVar3 = *(int **)(unaff_ESI + 8);  // +0x08 = freeListHead
  if (piVar3 == (int *)0x0) {
    // Allocate new block of 0x204 bytes
    iVar2 = FUN_009c8e50(0x204);  // rawAlloc(0x204)
    if (iVar2 == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      // Constructor for the new block? 
      piVar3 = (int *)FUN_00573c40();  // constructBlock?
    }
    // Initialize free list for 0x1f (31) elements, each element is 0x10 bytes
    iVar2 = 0x1f;
    piVar1 = piVar3;
    do {
      // Each element: pointer to next free element at offset +4
      piVar1[4] = (int)(piVar1 + 5);  // +0x04 = nextFree, points to next element
      iVar2 = iVar2 + -1;
      piVar1 = piVar1 + 4;
    } while (iVar2 != 0);
    piVar3[0x80] = 0;  // Last element's nextFree = null
    // Add new block to allocation block list
    *piVar3 = *(int *)(unaff_ESI + 0x10);  // +0x10 = blockList (linked list)
    *(int **)(unaff_ESI + 0x10) = piVar3;  // Update blockList head
    piVar3 = piVar3 + 1;  // Skip block header (first element)
    *(int **)(unaff_ESI + 8) = piVar3;  // Set freeListHead to first free element
  }
  // Pop from free list
  *(int *)(unaff_ESI + 8) = piVar3[3];  // +0x0c? No, offset = 12 bytes = piVar3[3]
  piVar3[3] = 0;  // Clear freed element's next pointer
  *(int *)(unaff_ESI + 0xc) = *(int *)(unaff_ESI + 0xc) + 1;  // +0x0c = usedCount
  return;
}