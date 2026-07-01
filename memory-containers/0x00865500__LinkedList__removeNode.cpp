// FUNC_NAME: LinkedList::removeNode
void __thiscall LinkedList::removeNode(int *list, undefined4 param_2, int *node)
{
  int *currentNode;
  int nextNode;
  int *unaff_EBX;
  
  currentNode = (int *)*node;
  if (currentNode == (int *)0x0) {
    nextNode = 0;
  }
  else {
    nextNode = currentNode[7]; // +0x1C: next pointer
  }
  *node = nextNode;
  if (currentNode == (int *)*list) { // head
    if (currentNode == (int *)list[1]) { // tail
      list[1] = 0; // tail = null
      *list = 0;   // head = null
    }
    else {
      nextNode = currentNode[7]; // +0x1C: next
      *list = nextNode; // head = next
      if (nextNode != 0) {
        *(undefined4 *)(nextNode + 0x20) = 0; // +0x20: prev = null
      }
    }
  }
  else {
    nextNode = currentNode[8]; // +0x20: prev pointer
    if (currentNode == (int *)list[1]) { // tail
      list[1] = nextNode; // tail = prev
      *(undefined4 *)(nextNode + 0x1c) = 0; // +0x1C: next = null
    }
    else {
      *(int *)(nextNode + 0x1c) = currentNode[7]; // prev->next = current->next
      *(int *)(currentNode[7] + 0x20) = currentNode[8]; // current->next->prev = current->prev
    }
  }
  if (currentNode[3] != 0) { // +0x0C: some pointer
    FUN_004daf90(currentNode + 3); // free memory at +0x0C
  }
  if (*currentNode != 0) { // +0x00: some pointer
    FUN_004daf90(currentNode); // free memory at +0x00
  }
  (**(code **)(*(int *)list[4] + 4))(currentNode, 0); // call destructor via vtable at list[4] (allocator?)
  list[2] = list[2] + -1; // decrement count
  *unaff_EBX = *node; // update output
  return;
}