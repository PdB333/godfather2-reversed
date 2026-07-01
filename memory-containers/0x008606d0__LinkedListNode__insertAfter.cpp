// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode_insertAfter(int *this, int newNode, int userData)
{
  // this[0] = next pointer, this[1] = prev pointer, this[2] = data
  // newNode: the node to insert after this node
  // userData: value to store in the new node's data field
  if (*this == newNode) {
    // Already pointing to the same node, just set data
    this[2] = userData;
    return;
  }
  if (*this != 0) {
    // Remove old next node from list (FUN_004daf90 likely does unlink/remove)
    FUN_004daf90(this);  // unlinkOld(this)
  }
  *this = newNode;
  if (newNode != 0) {
    // Link this node into the list: set prev of new node to point back to us
    this[1] = *(int *)(newNode + 4);  // store old prev of new node
    *(int **)(newNode + 4) = this;    // new node's prev = this
    this[2] = userData;
    return;
  }
  // newNode is null, just set data
  this[2] = userData;
  return;
}