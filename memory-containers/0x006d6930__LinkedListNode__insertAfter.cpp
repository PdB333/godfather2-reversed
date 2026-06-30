// FUNC_NAME: LinkedListNode::insertAfter
int * __thiscall LinkedListNode::insertAfter(int *this, int *nodeToInsertAfter)
{
  // If nodeToInsertAfter is null, treat as inserting at head (offset 0)
  // Otherwise, advance to the "next" pointer field at +0x48
  int *targetNext;
  if (nodeToInsertAfter == (int *)0x0) {
    targetNext = (int *)0x0;
  }
  else {
    targetNext = (int *)((int)nodeToInsertAfter + 0x48); // +0x48: next pointer in node
  }
  
  // If this node's next pointer already points to targetNext, do nothing
  if (*this != (int)targetNext) {
    // Remove this node from its current list if it's already linked
    if (*this != 0) {
      FUN_004daf90(this); // likely LinkedListNode::remove or unlink
    }
    // Set this node's next pointer to targetNext
    *this = (int)targetNext;
    // If targetNext is non-null, update the previous node's next pointer to point to this node
    if (targetNext != (int *)0x0) {
      this[1] = *(int *)((int)targetNext + 4); // +0x04: previous pointer in target's node
      *(int **)((int)targetNext + 4) = this;   // update target's previous to this
    }
  }
  return this;
}