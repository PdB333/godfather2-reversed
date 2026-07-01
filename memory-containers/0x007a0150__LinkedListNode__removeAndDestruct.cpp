// FUNC_NAME: LinkedListNode::removeAndDestruct
int __thiscall LinkedListNode::removeAndDestruct(int this, byte param_2)
{
  // Set vtable pointer at +0x28
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // If there is a previous node (+0x18)
  if (*(int *)(this + 0x18) != 0) {
    // If there is no next node (+0x1c), update previous node's next pointer (+0x04)
    if (*(int *)(this + 0x1c) == 0) {
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Otherwise update next node's previous pointer (+0x08)
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    // If there is a data pointer (+0x20), update its previous pointer (+0x04)
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call base destructor
  FUN_0064d150();
  
  // If param_2 & 1 is set, free memory
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}