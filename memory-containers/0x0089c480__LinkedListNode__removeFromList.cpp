// FUNC_NAME: LinkedListNode::removeFromList
int __thiscall LinkedListNode::removeFromList(int this, byte param_2)
{
  // vtable pointer at +0x28
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // Check if list is not empty (head pointer at +0x18)
  if (*(int *)(this + 0x18) != 0) {
    // If no previous node (this is head), update head's next pointer
    if (*(int *)(this + 0x1c) == 0) {
      // +0x18 = head, +0x1c = prev, +0x20 = next
      // Update head's next pointer (head + 4 = next)
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Update previous node's next pointer (prev + 8 = next)
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    // If next node exists, update its prev pointer (next + 4 = prev)
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  FUN_0064d150();
  
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}