// FUNC_NAME: LinkedListNode::remove
void __fastcall LinkedListNode::remove(int this)
{
  // Remove this node from a doubly-linked list
  // +0x38: pointer to some callback/function pointer
  // +0x44: vtable or function pointer for callback
  if (*(int *)(this + 0x38) != 0) {
    (**(code **)(this + 0x44))(*(int *)(this + 0x38));
  }
  
  // +0x28: vtable pointer, set to a static sentinel/terminator
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // +0x18: previous node pointer
  // +0x1c: next node pointer
  // +0x20: data pointer (or some value)
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      // No next node, update previous node's next pointer (offset +0x4)
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Update next node's previous pointer (offset +0x8)
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    if (*(int *)(this + 0x20) != 0) {
      // Update data pointer's previous pointer (offset +0x4)
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  // Call some cleanup function
  FUN_0064d150();
  return;
}