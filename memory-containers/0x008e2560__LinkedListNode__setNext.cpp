// FUNC_NAME: LinkedListNode::setNext
int * __thiscall LinkedListNode::setNext(int *this, int *newNext)
{
  int *node;
  
  if (newNext == (int *)0x0) {
    node = (int *)0x0;
  }
  else {
    node = (int *)((int)newNext + 0x48);
  }
  
  // Check if current next pointer differs from new one
  if (*this != (int)node) {
    // Remove current node from its list if it's attached
    if (*this != 0) {
      FUN_004daf90(this);  // Unlink node from current list
    }
    *this = (int)node;
    
    // Attach to new node's previous pointer
    if (node != (int *)0x0) {
      this[1] = *(int *)((int)node + 4);  // Save old prev of new node
      *(int **)((int)node + 4) = this;     // Set new node's prev to this
    }
  }
  
  return this;
}