// FUNC_NAME: LinkedListNode::insertAfter
int * __thiscall LinkedListNode::insertAfter(int *thisNode, int *newNode)
{
  if (newNode == nullptr) {
    newNode = nullptr;
  }
  else {
    newNode = newNode + 0x48; // offset to next pointer? (newNode->next)
  }
  if (*thisNode != newNode) {
    if (*thisNode != 0) {
      // Remove current next reference? Or detach?
      FUN_004daf90(thisNode);
    }
    *thisNode = newNode;
    if (newNode != 0) {
      thisNode[1] = *(int *)(newNode + 4); // thisNode->prev = newNode->prev?
      *(int **)(newNode + 4) = thisNode; // newNode->prev = thisNode
    }
  }
  return thisNode;
}