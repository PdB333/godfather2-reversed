// FUNC_NAME: SomeContainer::removeNode
int * __thiscall SomeContainer::removeNode(int *this, int *node, int *listHead, int *listTail)
{
  int current;
  int prev;
  
  current = *(int *)(listHead + 8);  // +0x8: next pointer in linked list node
  node[1] = (int)listTail;           // store tail pointer
  *node = current;                   // store current head's next
  while (current == 0) {
    node[1] = node[1] + 4;           // advance tail pointer by 4 bytes
    current = *(int *)node[1];       // read next pointer
    *node = current;                 // update head
  }
  current = *listTail;               // get first node in list
  if (current == listHead) {
    *listTail = *(int *)(current + 8);  // update tail to next node
  }
  else {
    for (prev = *(int *)(current + 8); prev != listHead; prev = *(int *)(prev + 8)) {
      current = prev;
    }
    *(int *)(current + 8) = *(int *)(prev + 8);  // unlink node from list
  }
  FUN_009c8f10(listHead);            // free or deallocate the node
  *(int *)(this + 0xc) = *(int *)(this + 0xc) + -1;  // decrement count at +0xC
  return node;
}