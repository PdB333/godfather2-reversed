// FUNC_NAME: LinkedListNode::addAfter
// This is a standard doubly linked list node insertion function (add after).
// param_1 (this): the node to insert after another node (param_2)
// param_2: the node after which to insert param_1
int * __thiscall LinkedListNode::addAfter(int *this, int *nodeToInsertAfter)
{
  int *existingNext; // *param_2, the next pointer of the node we're inserting after
  
  if (this != nodeToInsertAfter) {
    existingNext = (int *)*nodeToInsertAfter; // get the current next of the target node
    if (*this != (int)existingNext) {
      if (*this != 0) {
        // Remove this node from its current list if it's already linked
        FUN_004daf90(this); // likely removeNode or unlink
      }
      *this = (int)existingNext; // point this->next to existingNext
      if (existingNext != (int *)0x0) {
        this[1] = (int)nodeToInsertAfter; // this->prev = nodeToInsertAfter
        *(int **)((int)existingNext + 4) = this; // existingNext->prev = this
      }
    }
    return this;
  }
  return this;
}