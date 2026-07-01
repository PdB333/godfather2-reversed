// FUNC_NAME: LinkedListNode::insertAfter
int * __thiscall LinkedListNode::insertAfter(int *this, int *nodeToInsertAfter)
{
  int *targetNode;
  
  if (nodeToInsertAfter == (int *)0x0) {
    targetNode = (int *)0x0;
  }
  else {
    targetNode = nodeToInsertAfter + 0x48;
  }
  if (*this != targetNode) {
    if (*this != (int)0x0) {
      FUN_004daf90(this); // removeFromList
    }
    *this = targetNode;
    if (targetNode != (int *)0x0) {
      this[1] = *(int *)(targetNode + 4); // this->next = targetNode->next
      *(int **)(targetNode + 4) = this;   // targetNode->next = this
    }
  }
  return this;
}