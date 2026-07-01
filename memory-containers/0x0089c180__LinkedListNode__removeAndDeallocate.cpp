// FUNC_NAME: LinkedListNode::removeAndDeallocate
int __thiscall LinkedListNode::removeAndDeallocate(int this, byte deallocateFlag)
{
  // Set vtable pointer (likely base class or interface)
  *(void ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // If next pointer is not null
  if (*(int *)(this + 0x18) != 0) {
    // If prev pointer is null, update head's next
    if (*(int *)(this + 0x1c) == 0) {
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Otherwise update prev's next
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    // If data pointer is not null, update its prev
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call some cleanup function
  FUN_0064d150();
  
  // If deallocate flag is set, free memory
  if ((deallocateFlag & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}