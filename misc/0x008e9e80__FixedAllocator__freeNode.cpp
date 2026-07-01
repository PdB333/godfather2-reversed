// FUNC_NAME: FixedAllocator::freeNode
void __thiscall FixedAllocator::freeNode(int thisPtr, int *nodePtr)
{
  int *nextFreeNode;
  int *prevFreeNode;
  
  // Get the next free node from the node being freed
  nextFreeNode = (int *)*nodePtr;
  // Update the free list head to point to the next node
  *nodePtr = *(int *)((int)nextFreeNode + 8);
  
  // If the next free node is not the end marker
  if (*(char *)(*(int *)((int)nextFreeNode + 8) + 0x25) == '\0') {
    // Update the previous pointer of the next free node
    *(int **)(*(int *)((int)nextFreeNode + 8) + 4) = nodePtr;
  }
  
  // Set the node's back pointer to the previous node in the free list
  *(int *)((int)nextFreeNode + 4) = nodePtr[1];
  
  // If the node being freed is the last in the free list
  if (nodePtr == *(int **)(*(int *)(thisPtr + 4) + 4)) {
    // Update the tail pointer to point to the freed node
    *(int *)(*(int *)(thisPtr + 4) + 4) = (int)nextFreeNode;
    // Link the freed node back into the free list
    *(int **)((int)nextFreeNode + 8) = nodePtr;
    nodePtr[1] = (int)nextFreeNode;
    return;
  }
  
  // Get the previous node in the free list
  prevFreeNode = (int *)nodePtr[1];
  
  // If the previous node's next pointer points to the node being freed
  if (nodePtr == (int *)prevFreeNode[2]) {
    // Update the previous node's next pointer to the freed node
    prevFreeNode[2] = (int)nextFreeNode;
    // Link the freed node back into the free list
    *(int **)((int)nextFreeNode + 8) = nodePtr;
    nodePtr[1] = (int)nextFreeNode;
    return;
  }
  
  // Otherwise, update the previous node's data pointer
  *prevFreeNode = (int)nextFreeNode;
  // Link the freed node back into the free list
  *(int **)((int)nextFreeNode + 8) = nodePtr;
  nodePtr[1] = (int)nextFreeNode;
  return;
}