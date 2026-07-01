// FUNC_NAME: SomeClass::findOrCreateByID
undefined4 __thiscall SomeClass::findOrCreateByID(int this, undefined4 param_2, uint id)
{
  int node;
  
  node = *(int *)(this + 0x60); // +0x60: linked list head pointer
  if (node != 0) {
    while ((int)*(short *)(node + 0x44) != id) { // +0x44: node ID (short)
      if (id < (uint)(int)*(short *)(node + 0x44)) {
        return 2; // not found, id less than current node
      }
      node = *(int *)(node + 4); // +0x04: next node pointer
      if (node == 0) {
        return 2; // end of list, not found
      }
    }
    // Found node with matching ID
    if (*(int *)(node + 0x38) != 0) { // +0x38: some resource pointer
      FUN_004df630(); // likely release/delete resource
    }
    if (*(int *)(node + 0x3c) != 0) { // +0x3c: another resource pointer
      FUN_004df630(); // likely release/delete resource
    }
  }
  return 2; // always returns 2 (maybe success code or unused)
}