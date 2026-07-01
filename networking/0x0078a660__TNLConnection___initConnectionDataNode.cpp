// FUNC_NAME: TNLConnection::_initConnectionDataNode
void __thiscall FUN_0078a660(undefined4 *this, int param_2)

{
  // Set vtable pointer (likely a node object with pointer to functions)
  *this = &PTR_FUN_00d69a28;
  
  // If param_2 (likely parent/sibling node) is 0, keep as null
  // Otherwise offset by 0x48 bytes (connection data structure offset)
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48;  // +0x48: offset to link field inside connection data
  }
  
  // +0x00: this[0] = vtable pointer
  // +0x04: this[1] = next node pointer (or null)
  // +0x08: this[2] = previous node pointer (or null)
  this[1] = param_2;
  this[2] = 0;
  
  // If we have a valid connection data pointer, link this node into the list
  // The node has a doubly-linked list structure at +0x04 and +0x08
  // The connection data has a "lastNode" pointer at +0x04
  if (param_2 != 0) {
    // Save current "previous" pointer from connection data's lastNode
    this[2] = *(undefined4 *)(param_2 + 4);
    // Update connection data's lastNode to point to this node
    *(undefined4 **)(param_2 + 4) = this + 1;
  }
  return;
}