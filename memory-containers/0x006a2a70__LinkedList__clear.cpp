// FUNC_NAME: LinkedList::clear
void __thiscall LinkedList::clear(LinkedList *this)
{
  LinkedList *current;
  LinkedList *next;

  // Traverse the list starting from the sentinel's next node
  current = this->next;  // *param_1 is this->next (offset 0)
  while (current != this) {  // until we reach sentinel
    next = current->next;  // store next before destroying
    destroyNode(current);  // FUN_009c8f10: free node
    current = next;
  }
  // Reset sentinel to point to itself (empty list)
  this->next = this;  // *param_1 = param_1
  this->prev = this;  // param_1[1] = param_1
}