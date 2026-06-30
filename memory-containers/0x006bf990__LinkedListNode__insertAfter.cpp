// FUNC_NAME: LinkedListNode::insertAfter
int * __thiscall LinkedListNode::insertAfter(int *this, int *node)
{
  int *nextNode;
  
  if (this != node) {
    nextNode = (int *)*node;
    if (*this != (int)nextNode) {
      if (*this != 0) {
        LinkedListNode::remove(this);
      }
      *this = (int)nextNode;
      if (nextNode != (int *)0x0) {
        this[1] = *(int *)((int)nextNode + 4); // +0x4: prev pointer
        *(int **)((int)nextNode + 4) = this; // +0x4: prev pointer
      }
    }
    return this;
  }
  return this;
}