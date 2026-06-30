// FUNC_NAME: NodeList::removeNode
void __thiscall NodeList::removeNode(NodeList *this, ListNode *node)
{
  // Decrement node count
  this->count--; // +0xCC

  // Call internal cleanup (likely notifications or bookkeeping)
  FUN_00448880();

  // Remove from first linked list (pointers at offsets +0xC and +0x10)
  if (node->prev1 != NULL) // +0xC
  {
    // Set previous node's next to the node's next
    node->prev1->next1 = node->next1; // +0x10
  }
  if (node->next1 != NULL) // +0x10
  {
    // Set next node's prev to the node's prev
    node->next1->prev1 = node->prev1; // +0xC
  }
  // Clear the node's links for the first list
  node->next1 = NULL; // +0x10
  node->prev1 = NULL; // +0xC

  // Remove from second linked list (pointers at offsets +0x4 and +0x8)
  if (node->prev2 != NULL) // +0x4
  {
    node->prev2->next2 = node->next2; // +0x8
  }
  if (node->next2 != NULL) // +0x8
  {
    node->next2->prev2 = node->prev2; // +0x4
  }
  // Clear the node's links for the second list
  node->next2 = NULL; // +0x8
  node->prev2 = NULL; // +0x4
}