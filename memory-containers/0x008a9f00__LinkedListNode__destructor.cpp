// FUNC_NAME: LinkedListNode::destructor
int __thiscall LinkedListNode::~LinkedListNode(int this, byte flags)
{
  // Set vtable pointers (likely for base class or interface)
  *(undefined ***)(this + 0x38) = &PTR_LAB_00e35c24;
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // Unlink this node from the doubly-linked list
  // +0x18: prev pointer
  // +0x1c: next pointer
  // +0x20: data pointer (or self-reference)
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      // No next node, update prev's next pointer
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Update next's prev pointer
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    if (*(int *)(this + 0x20) != 0) {
      // Update data's prev pointer (or self's next pointer)
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call base destructor
  FUN_0064d150();
  
  // If flags has bit 0 set, free memory (operator delete)
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}