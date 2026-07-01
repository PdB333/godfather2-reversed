// FUNC_NAME: LinkedListNode::destructor
int __thiscall LinkedListNode::destructor(int this, byte flags)
{
  // Set vtable pointer at +0x28
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // If there's a previous node (+0x18)
  if (*(int *)(this + 0x18) != 0) {
    // If no next node (+0x1c == 0), update previous node's next pointer (+0x04)
    if (*(int *)(this + 0x1c) == 0) {
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    // Otherwise update previous node's next pointer (+0x08)
    else {
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    // If there's a next node (+0x20), update its previous pointer (+0x04)
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call base destructor
  FUN_0064d150();
  
  // If flags has bit 0 set, free memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}