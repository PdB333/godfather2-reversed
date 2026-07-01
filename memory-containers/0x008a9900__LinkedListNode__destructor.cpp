// FUNC_NAME: LinkedListNode::destructor
int __thiscall LinkedListNode::~LinkedListNode(int this, byte flags)
{
  // Set vtable pointer +0x28
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // Remove this node from a doubly-linked list using head/tail pointers
  // Structure appears to be:
  // +0x00: data/unknown
  // +0x04: unknown
  // +0x08: unknown
  // +0x18: prev pointer
  // +0x1c: next pointer
  // +0x20: self pointer (back-link)
  // +0x28: vtable
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      // No next node, so this is the tail - update prev's next to point to self->next (the node after this)
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Has next node - update prev's next to point to next
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    // If self pointer is not null, update the node at self pointer to point backward to prev
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  FUN_0064d150(); // Possibly base destructor or memory cleanup
  
  // If bit 0 of flags is set, free the memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this); // operator delete(this)
  }
  
  return this;
}