// FUNC_NAME: GenericList::addNode
int __thiscall GenericList::addNode(int this, undefined4 param_2)
{
  int newNode;
  int *nodeEntry;
  int oldCapacity;
  int *newEntry;
  
  newNode = FUN_009c8e50(0x44); // allocate node data (68 bytes)
  if (newNode == 0) {
    newNode = 0;
  }
  else {
    newNode = FUN_008c96f0(param_2); // initialize node with param_2
  }
  
  // Allocate a list entry (8 bytes: pointer to node + next pointer)
  nodeEntry = (int *)FUN_009c8e50(8);
  newEntry = (int *)0x0;
  if (nodeEntry != (int *)0x0) {
    *nodeEntry = newNode;
    nodeEntry[1] = 0;
    newEntry = nodeEntry;
    if (newNode != 0) {
      // Insert into linked list at head (node +0x4 is head pointer)
      nodeEntry[1] = *(int *)(newNode + 4);
      *(int **)(newNode + 4) = nodeEntry;
    }
  }
  
  // Grow the array if needed
  oldCapacity = *(int *)(this + 0xc); // +0x0C: capacity
  if (*(int *)(this + 8) == oldCapacity) { // +0x08: count
    if (oldCapacity == 0) {
      oldCapacity = 1;
    }
    else {
      oldCapacity = oldCapacity * 2;
    }
    FUN_008c9f90(oldCapacity); // resize array
  }
  
  // Add entry to array
  nodeEntry = (int *)(*(int *)(this + 4) + *(int *)(this + 8) * 4); // +0x04: array pointer
  *(int *)(this + 8) = *(int *)(this + 8) + 1; // increment count
  if (nodeEntry != (int *)0x0) {
    *nodeEntry = (int)newEntry;
  }
  
  *(undefined1 *)(this + 0x10) = 1; // +0x10: dirty flag
  return newNode;
}