// FUNC_NAME: CRefCountedSet::clearAll
void CRefCountedSet::clearAll(void)
{
  unsigned int i;
  Node *node;
  DataObject *data;
  unsigned short flags;
  char refCount;
  Node *head;
  Node *prev;
  Node *cur;

  // Iterate over all nodes in the array
  for (i = 0; i < this->count; i++) {
    node = this->nodeArray[i];  // *(int **)(*(int *)(this + 0x2c) + i*4)
    // If node has a valid bucket head, decrement the associated data's reference count
    if (node->bucketHead != 0) {
      data = node->data;
      data->refCount--;
      // If reference count reaches zero, clear bit 0x8000 in flags
      if (data->refCount == 0) {
        data->flags &= ~0x8000;
      }
    }
    // Remove node from its bucket's linked list
    if (node != 0) {
      head = node->bucketHead;  // *piVar3
      if (head != 0) {
        // Find the node in the singly linked list starting from head->next
        prev = head->next;
        if (prev == node) {
          head->next = node->next;
        } else {
          cur = prev->next;
          while (cur != node) {
            prev = cur;
            cur = prev->next;
          }
          prev->next = node->next;
        }
      }
      // Free the node itself
      FreeMemory(node);
    }
  }
  // Reset count, free the array, and zero out members
  this->count = 0;
  FreeMemory(this->nodeArray);
  this->nodeArray = 0;
  this->unknown34 = 0;
}