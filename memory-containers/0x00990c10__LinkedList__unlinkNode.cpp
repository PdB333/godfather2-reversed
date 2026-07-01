// FUNC_NAME: LinkedList::unlinkNode
void __thiscall LinkedList::unlinkNode(int *this, int *node)
{
  int *prev;
  int *next;
  
  prev = (int *)node[2]; // +0x8: previous node pointer
  next = (int *)node[1]; // +0x4: next node pointer
  
  if (prev == 0) {
    // Node is head of list
    *this = (int)next;
    if (next != 0) {
      next[2] = 0; // next->prev = NULL
    }
  } else {
    prev[1] = (int)next; // prev->next = next
  }
  
  if (next != 0) {
    next[2] = (int)prev; // next->prev = prev
    node[2] = 0; // node->prev = NULL
    node[1] = 0; // node->next = NULL
    return;
  }
  
  // Node was tail of list
  this[1] = (int)prev; // update tail pointer
  if (prev != 0) {
    prev[1] = 0; // prev->next = NULL
  }
  node[2] = 0; // node->prev = NULL
  node[1] = 0; // node->next = NULL
}