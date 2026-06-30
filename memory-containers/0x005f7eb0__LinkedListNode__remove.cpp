// FUNC_NAME: LinkedListNode::remove
int * __thiscall LinkedListNode::remove(int *thisNode, byte flags)
{
  int headNode;
  int *prevNode;
  int *nextNode;
  
  headNode = *thisNode; // head of list
  if (headNode != 0) {
    prevNode = *(int **)(headNode + 4); // head->prev
    if (prevNode == thisNode) {
      // this node is head->prev (i.e., head->next? or head->prev?)
      *(int *)(headNode + 4) = thisNode[1]; // head->prev = this->next
    }
    else {
      nextNode = (int *)prevNode[1]; // prev->next
      while (nextNode != thisNode) {
        prevNode = (int *)prevNode[1]; // prev = prev->next
        nextNode = (int *)prevNode[1]; // next = prev->next
      }
      prevNode[1] = thisNode[1]; // prev->next = this->next
    }
  }
  if ((flags & 1) != 0) {
    FUN_009c8eb0(thisNode); // free memory
  }
  return thisNode;
}