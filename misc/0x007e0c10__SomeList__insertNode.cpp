// FUNC_NAME: SomeList::insertNode
void __thiscall SomeList::insertNode(int this, int node)
{
  int **ppListHead;
  
  ppListHead = (int **)(this + 0x124);
  if (node == 0) {
    node = 0;
  }
  else {
    node = node + 0x48;
  }
  if (*ppListHead != node) {
    if (*ppListHead != 0) {
      FUN_004daf90(ppListHead); // likely removeNode or unlink
    }
    *ppListHead = node;
    if (node != 0) {
      *(int *)(this + 0x128) = *(int *)(node + 4); // +0x128: next pointer
      *(int **)(node + 4) = ppListHead;            // +0x04: prev pointer
    }
  }
  return;
}