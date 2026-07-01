// FUNC_NAME: LinkedListNode::insertAfter
int * __thiscall LinkedListNode::insertAfter(int *this, int *node)
{
  int *target;
  
  if (node == 0) {
    target = 0;
  }
  else {
    target = node + 0x48; // +0x48: offset to next pointer in node
  }
  
  if (*this != target) {
    if (*this != 0) {
      FUN_004daf90(this); // remove this from current list
    }
    *this = target;
    if (target != 0) {
      this[1] = *(int *)(target + 4); // +0x04: previous pointer
      *(int **)(target + 4) = this;   // set node's previous to this
    }
  }
  return this;
}