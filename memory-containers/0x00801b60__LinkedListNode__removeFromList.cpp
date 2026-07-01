// FUNC_NAME: LinkedListNode::removeFromList
int __thiscall LinkedListNode::removeFromList(int this, byte param_2)
{
  // Set vtable pointer at +0x28
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // If next pointer (+0x18) is not null
  if (*(int *)(this + 0x18) != 0) {
    // If prev pointer (+0x1c) is null, we are the head
    if (*(int *)(this + 0x1c) == 0) {
      // Update next node's prev to our prev (which is null, so head becomes next)
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Update next node's prev to our prev
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    // If our prev (+0x20) is not null
    if (*(int *)(this + 0x20) != 0) {
      // Update prev node's next to our next
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call some cleanup function
  FUN_0064d150();
  
  // If param_2 & 1 is set, call destructor
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}