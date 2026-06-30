// FUNC_NAME: LinkedListNode::replaceWith
int * __thiscall LinkedListNode::replaceWith(int *this, int *newNode)
{
  int iVar1;
  
  if (this != newNode) {
    iVar1 = *newNode;
    if (*this != iVar1) {
      if (*this != 0) {
        // Remove current node from its list
        FUN_004daf90(this);
      }
      *this = iVar1;
      if (iVar1 != 0) {
        // Link this node into the list after the new node's original position
        this[1] = *(int *)(iVar1 + 4);  // +0x4: next pointer
        *(int **)(iVar1 + 4) = this;    // +0x4: update next pointer of previous node
      }
    }
    return this;
  }
  return this;
}