// FUNC_NAME: LinkedListNode::~LinkedListNode
int __thiscall LinkedListNode::~LinkedListNode(int this, byte deleteFlag)
{
  // Set vtable pointer to base class vtable (destructor vtable)
  *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

  // Remove this node from a doubly linked list
  // Offsets: +0x18 = prev, +0x1c = next, +0x20 = owner pointer
  int* prev = *(int**)(this + 0x18);
  int* next = *(int**)(this + 0x1c);
  int* owner = *(int**)(this + 0x20);

  if (prev != 0) {
    if (next == 0) {
      // This is the last node; update previous node's "next" pointer (at +4) to owner
      *(prev + 1) = owner; // prev->next = owner
    } else {
      // Update next node's "prev" pointer (at +8) to owner
      *(next + 2) = owner; // next->prev = owner
    }
  }

  if (owner != 0) {
    // Update owner's "next" pointer (at +4) to this node's next
    *(owner + 1) = next; // owner->next = this->next
  }

  // Call base class destructor
  FUN_0064d150();

  // If deleteFlag & 1, deallocate memory
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this); // operator delete
  }

  return this;
}