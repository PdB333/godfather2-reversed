// FUNC_NAME: LinkedListNode::destructor
int __thiscall LinkedListNode_destructor(int this, byte flags)
{
  // Call destructor on the data pointer at +0x38
  if (*(int *)(this + 0x38) != 0) {
    (**(code **)(this + 0x44))(*(int *)(this + 0x38));
  }
  // Set vtable pointer at +0x28
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc;
  // Unlink this node from the doubly-linked list
  // +0x18 = prev, +0x1c = next, +0x20 = data
  if (*(int *)(this + 0x18) != 0) {
    if (*(int *)(this + 0x1c) == 0) {
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20);
    }
    else {
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20);
    }
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c);
    }
  }
  FUN_0064d150();
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  return this;
}