// FUNC_NAME: LinkedListNode::insertAfter
int * __thiscall LinkedListNode::insertAfter(int *this, int *nodeToInsertAfter)
{
  int *targetNode;
  
  if (nodeToInsertAfter == (int *)0x0) {
    targetNode = (int *)0x0;
  }
  else {
    targetNode = nodeToInsertAfter + 0x12; // +0x48 offset for next pointer
  }
  
  if (*this != targetNode) {
    if (*this != (int *)0x0) {
      FUN_004daf90(this); // removeFromList
    }
    *this = targetNode;
    if (targetNode != (int *)0x0) {
      this[1] = *(int *)(targetNode + 1); // copy previous next pointer
      *(int **)(targetNode + 1) = this;   // update target's next to point to this
    }
  }
  
  return this;
}