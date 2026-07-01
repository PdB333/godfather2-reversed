// FUNC_NAME: LinkedList::removeByKey
void __thiscall LinkedList::removeByKey(undefined4 *this, int *key)
{
  undefined4 *current;
  int *nodeKey;
  
  current = (undefined4 *)*this;
  while (current != this) {
    nodeKey = current + 2;
    current = (undefined4 *)*current;
    if (*nodeKey == *key) {
      // Unlink node from doubly-linked list
      int *prev = (int *)current[1];
      *(int *)prev[1] = *prev;
      *(int *)(*prev + 4) = prev[1];
      // Free node data if present
      if (prev[2] != 0) {
        FUN_004daf90(prev + 2); // likely operator delete or free
      }
      FUN_009c8f10(prev); // likely node destructor or deallocation
    }
  }
  return;
}