// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode::insertAfter(int *this, int newNode, int userData)
{
  // this[0] = next pointer, this[1] = prev pointer, this[2] = user data
  if (*this == newNode) {
    this[2] = userData;
    return;
  }
  if (*this != 0) {
    // Remove from current list
    FUN_004daf90(this);
  }
  *this = newNode;
  if (newNode != 0) {
    // newNode+4 is the prev pointer of the node after newNode
    this[1] = *(int *)(newNode + 4); // +0x4: prev pointer
    *(int **)(newNode + 4) = this;   // newNode->prev = this
    this[2] = userData;              // +0x8: user data
    return;
  }
  this[2] = userData;
  return;
}