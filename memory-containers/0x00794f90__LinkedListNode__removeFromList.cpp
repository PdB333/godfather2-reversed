// FUNC_NAME: LinkedListNode::removeFromList
int __thiscall LinkedListNode::removeFromList(int this, byte freeFlag)
{
  // +0x28: vtable pointer (set to something)
  *(void (***)())(this + 0x28) = &PTR_LAB_00e317cc;
  
  // +0x18: prev pointer
  // +0x1c: next pointer  
  // +0x20: data pointer (or value)
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      // No next node - update prev's next pointer
      *(int *)(*(int *)(this + 0x18) + 4) = *(int *)(this + 0x20);
    }
    else {
      // Has next node - update next's prev pointer
      *(int *)(*(int *)(this + 0x1c) + 8) = *(int *)(this + 0x20);
    }
    // Update data pointer's next pointer (circular list fix)
    if (*(int *)(this + 0x20) != 0) {
      *(int *)(*(int *)(this + 0x20) + 4) = *(int *)(this + 0x1c);
    }
  }
  
  FUN_0064d150(); // Possibly unlink or cleanup
  if ((freeFlag & 1) != 0) {
    FUN_009c8eb0(this); // operator delete(this)
  }
  return this;
}