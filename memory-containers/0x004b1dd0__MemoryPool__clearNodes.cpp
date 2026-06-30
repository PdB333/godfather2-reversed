// FUNC_NAME: MemoryPool::clearNodes
// This function clears a linked list of nodes (likely free list or allocated block list)
// and optionally deallocates the pool itself. param_2 (deleteFlag) bit 0 controls deletion.
// Each node is zeroed (16 bytes: two pointers/int + next pointer) before unlinking.
MemoryPool * __thiscall MemoryPool::clearNodes(MemoryPool *this, byte deleteFlag)
{
  // Set vtable pointer (base class vtable, likely to prevent virtual calls during destruction)
  this->vtable = (void * *)&PTR_LAB_00e42de4; // +0x00: vtable
  Node *current = (Node *)this->head; // +0x04: head of linked list (nodes contain field_0, field_4, next)
  while (current != (Node *)0x0) {
    Node *nextNode = current->next;           // +0x08: next pointer in node
    current->field_0 = 0;                     // +0x00: first field (int/pointer)
    current->field_4 = 0;                     // +0x04: second field (int/pointer)
    current->next = (Node *)0x0;               // +0x08: clear next link
    current = nextNode;
  }
  // If flag bit 0 is set, deallocate this pool (custom operator delete)
  if ((deleteFlag & 1) != 0) {
    MemoryPool::operatorDelete(this); // FUN_009c8eb0 (custom deallocation)
  }
  return this;
}