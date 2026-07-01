// FUNC_NAME: LinkedListNode::~LinkedListNode
int __thiscall LinkedListNode::~LinkedListNode(void *this, byte param_2)
{
  // Set vtable pointer to base class vtable (offset +0x28)
  *(void ***)((char *)this + 0x28) = &PTR_LAB_00e317cc;

  // Remove this node from a doubly linked list
  // Offsets: +0x18 = next, +0x1c = prev, +0x20 = data
  // The list structure has 'next' at offset 4 of the current node's next pointer,
  // and 'prev' at offset 8 of the current node's prev pointer.
  // This is typical for a list where each node stores a pointer to the head/tail of the list.
  if (*(void **)((char *)this + 0x18) != 0) {
    if (*(void **)((char *)this + 0x1c) == 0) {
      // If prev is null, update next->next (offset 4) to point to data
      *(void **)((char *)*(void **)((char *)this + 0x18) + 4) = *(void **)((char *)this + 0x20);
    } else {
      // Otherwise update prev->prev (offset 8) to point to data
      *(void **)((char *)*(void **)((char *)this + 0x1c) + 8) = *(void **)((char *)this + 0x20);
    }

    if (*(void **)((char *)this + 0x20) != 0) {
      // Update data->next (offset 4) to point to prev
      *(void **)((char *)*(void **)((char *)this + 0x20) + 4) = *(void **)((char *)this + 0x1c);
    }
  }

  // Call base class destructor or shared cleanup function
  FUN_0064d150();

  // If param_2's least significant bit is set, deallocate the memory
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }

  return (int)this;
}