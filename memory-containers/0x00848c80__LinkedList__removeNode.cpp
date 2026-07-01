// FUNC_NAME: LinkedList::removeNode
undefined4 * __thiscall LinkedList::removeNode(undefined4 *this, undefined4 *node)
{
  // Remove node from doubly-linked list
  // +0x00: vtable pointer
  // +0x04: previous node pointer
  // +0x08: next node pointer
  
  if (this[1] != 0) {
    // Update previous node's next pointer to skip this node
    *(undefined4 *)(this[1] + 8) = this[2];
  }
  if (this[2] != 0) {
    // Update next node's previous pointer to skip this node
    *(undefined4 *)(this[2] + 4) = this[1];
  }
  
  // If the node being removed is the head, update head to next node
  if (node == this) {
    node = (undefined4 *)this[2];
  }
  
  // Call destructor via vtable (index 0)
  (**(code **)*this)(1);
  
  return node;
}