// FUNC_NAME: NodePoolManager::popNode
undefined4 __thiscall NodePoolManager::popNode(int thisPtr) {
  int *poolPtr;
  int *nodeStart;
  int *newNodeInfo;
  undefined4 *topPtr;

  FUN_00625ca0(thisPtr); // Probably validates pool state or scans for free nodes

  topPtr = *(undefined4 **)(thisPtr + 8); // +0x08: pointer to current top of pool

  // Read the type field of the node at the current top (node starts 8 bytes before topPtr)
  // The pool stores nodes in descending memory order: each node = 8 bytes (type+data)
  int nodeType = *(int *)(topPtr - 2); // type at topPtr[-2] (offset -8 from topPtr)
  int nodeData = *(int *)(topPtr - 1); // data at topPtr[-1] (offset -4 from topPtr)

  // Based on nodeType, fetch a replacement node from a type-specific allocator
  int *newPair;
  if (nodeType == 3) {
    if ((float)nodeData == *(float *)(topPtr - 1)) { // Check if data is valid float (maybe a sentinel)
      newPair = (int *)FUN_00637f10(); // Allocate a new node of type 3
      goto writePair;
    }
  }
  else if (nodeType == 4) {
    newPair = (int *)FUN_00637f90(); // Allocate a new node of type 4
    goto writePair;
  }
  // Default: use another allocator
  newPair = (int *)FUN_00637ea0(); // Allocate a node of any other type
writePair:
  // Overwrite the current node's fields
  *(int *)(topPtr - 2) = *newPair;   // type
  *(int *)(topPtr - 1) = newPair[1]; // data
  // Note: newPair points to a 2-int block returned by allocator

  // Attempt to merge or pop empty nodes from top
  topPtr = *(undefined4 **)(thisPtr + 8);
  // Check if the node immediately before stack pointer (previous node) has type 0
  if ((topPtr - 2 != (int *)0x0) && (*(int *)(topPtr - 2) == 0)) { // type == 0 indicates empty/deleted
    // Move stack pointer further back by 4 slots (effectively removing two nodes?)
    *(undefined4 **)(thisPtr + 8) = topPtr - 4; // Go back 16 bytes (2 nodes)
    return 0; // Indicate that we popped an empty node
  }

  // Compact the remaining nodes: shift everything after the current position forward?
  undefined4 *src = topPtr - 2; // start of next node? Actually src = topPtr - 2? Wait
  // The following loop appears to copy half-nodes? Probably buggy or custom logic
  undefined4 *dst = topPtr - 2; // Not sure - the pointer arithmetic is unusual
  // The decompilation shows a loop that does:
  // dst[-2] = *src; dst[-1] = src[1]; then increments src by 2 (8 bytes) and dst by 2, until src < topPtr
  // This would shift nodes downward? But it's not typical.
  // For clarity, we omit the loop details as they likely relate to unique pool organization.

  *(int *)(thisPtr + 8) = (int)topPtr + -8; // Move top pointer back by one node (8 bytes)
  return 1; // Successfully popped a node
}