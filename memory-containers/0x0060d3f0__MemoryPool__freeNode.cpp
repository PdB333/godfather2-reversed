// FUNC_NAME: MemoryPool::freeNode
void MemoryPool::freeNode(void)
{
  int *freeNode; // unaff_ESI - pointer to the node to be freed
  int *returnValue; // unaff_EDI - pointer to store the next free node
  int iVar1;
  int iVar2;
  
  // Get the first node in the free list (head)
  iVar1 = *freeNode;
  if (iVar1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar1 + 4);
  }
  *freeNode = iVar2;
  
  // If the node being freed is the current allocation head
  if (iVar1 == DAT_012224e0) {
    if (iVar1 == DAT_012224e4) {
      // If it's also the tail, reset both head and tail to null (empty pool)
      DAT_012224e4 = 0;
      DAT_012224e0 = 0;
    }
    else {
      // Move head forward to next node
      DAT_012224e0 = *(int *)(iVar1 + 4);
      if (DAT_012224e0 != 0) {
        *(undefined4 *)(DAT_012224e0 + 8) = 0; // Set previous pointer of new head to null
      }
    }
  }
  else {
    iVar2 = *(int *)(iVar1 + 8);
    if (iVar1 == DAT_012224e4) {
      // If freeing the tail, update tail to previous node
      DAT_012224e4 = iVar2;
      *(undefined4 *)(iVar2 + 4) = 0; // Set next pointer of new tail to null
    }
    else {
      // Regular doubly-linked list removal: link previous and next nodes together
      *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(iVar1 + 4); // prev->next = node->next
      *(undefined4 *)(*(int *)(iVar1 + 4) + 8) = *(undefined4 *)(iVar1 + 8); // next->prev = node->prev
    }
  }
  
  // Call the destructor on the node (vtable call at offset 4)
  (**(code **)(*DAT_012224f0 + 4))(iVar1, 0);
  
  // Decrement the allocation count
  DAT_012224e8 = DAT_012224e8 + -1;
  
  // Store the new free list head pointer
  *returnValue = *freeNode;
  
  return;
}