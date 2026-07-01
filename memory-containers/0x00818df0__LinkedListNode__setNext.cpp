// FUNC_NAME: LinkedListNode::setNext
int * __thiscall LinkedListNode::setNext(int *thisNode, int *newNext)
{
  if (thisNode[0] != newNext) {
    if (thisNode[0] != 0) {
      // Remove this node from the current list (unlink from previous next)
      FUN_004daf90(thisNode);
    }
    thisNode[0] = newNext;
    if (newNext != 0) {
      // Set this node's previous pointer to the newNext's previous pointer
      thisNode[1] = newNext[1];  // +0x04: previous pointer
      // Link newNext's previous node to this node
      *(int **)(newNext[1] + 4) = thisNode;  // +0x04: previous pointer of newNext's previous
    }
  }
  return thisNode;
}