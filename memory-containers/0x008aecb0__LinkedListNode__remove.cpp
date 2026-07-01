// FUNC_NAME: LinkedListNode::remove
void __fastcall LinkedListNode::remove(int this)
{
  FUN_00407430(); // likely base class destructor or cleanup
  *(undefined ***)(this + 0x28) = &PTR_LAB_00e317cc; // vtable pointer update
  
  // Remove this node from a doubly-linked list
  if (*(int *)(this + 0x18) != 0) { // +0x18 = prev pointer
    if (*(int *)(this + 0x1c) == 0) { // +0x1c = next pointer
      // Only prev exists (this is tail)
      *(undefined4 *)(*(int *)(this + 0x18) + 4) = *(undefined4 *)(this + 0x20); // +0x20 = data pointer
    }
    else {
      // Both prev and next exist
      *(undefined4 *)(*(int *)(this + 0x1c) + 8) = *(undefined4 *)(this + 0x20); // +0x8 = next->prev? or data
    }
    if (*(int *)(this + 0x20) != 0) {
      *(undefined4 *)(*(int *)(this + 0x20) + 4) = *(undefined4 *)(this + 0x1c); // data->next = this->next
    }
  }
  FUN_0064d150(); // likely memory deallocation or further cleanup
}