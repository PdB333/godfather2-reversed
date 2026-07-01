// FUNC_NAME: BaseNode::destructor
int __thiscall BaseNode::destructor(int this, byte flags)
{
  // Set vtable pointer (destructed state)
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // If this node is part of a doubly-linked list, remove it
  if (*(int *)(this + 0x18) != 0) {
    // +0x18: previous node pointer
    // +0x1c: next node pointer
    // +0x20: data pointer (value)
    if (*(int *)(this + 0x1c) == 0) {
      // No next node, update previous's "next" pointer (+4 offset from previous)
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Update next node's "prev" pointer (+8 offset from next)
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    if (*(int *)(this + 0x20) != 0) {
      // Update data pointer's "next" pointer (+4 offset)
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call base destructor chain
  FUN_0064d150();
  
  // If deletion flag is set, free memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}