// FUNC_NAME: LinkedListNode::destructor
int __thiscall LinkedListNode::~LinkedListNode(int this, byte flags)
{
  // +0x38: pointer to some object that needs cleanup
  if (*(int *)(this + 0x38) != 0) {
    // +0x44: vtable function for cleanup
    (**(code **)(this + 0x44))(*(int *)(this + 0x38));
  }
  
  // +0x28: vtable pointer, reset to base class vtable
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  
  // Unlink this node from a doubly-linked list
  // +0x18: previous node pointer
  // +0x1c: next node pointer
  // +0x20: data pointer
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      // No next node, update previous node's next pointer
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      // Update next node's previous pointer
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    if (*(int *)(this + 0x20) != 0) {
      // Update data pointer's previous pointer
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  
  FUN_0064d150(); // likely memory deallocation or cleanup
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this); // likely operator delete
  }
  return this;
}