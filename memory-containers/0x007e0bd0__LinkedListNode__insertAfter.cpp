// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode::insertAfter(int this, int newNode)
{
  int **ppPrevNext;
  
  ppPrevNext = (int **)(this + 0xe4); // +0xe4: pointer to "next" node in linked list
  if (newNode == 0) {
    newNode = 0;
  }
  else {
    newNode = newNode + 0x48; // +0x48: offset to "prev" pointer in node
  }
  if (*ppPrevNext != newNode) {
    if (*ppPrevNext != 0) {
      FUN_004daf90(ppPrevNext); // likely a reference counting or cleanup function
    }
    *ppPrevNext = newNode;
    if (newNode != 0) {
      *(int *)(this + 0xe8) = *(int *)(newNode + 4); // +0xe8: store previous next's prev pointer
      *(int **)(newNode + 4) = ppPrevNext; // update the new node's prev to point back to this
    }
  }
  return;
}