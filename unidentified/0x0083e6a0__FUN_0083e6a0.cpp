// FUNC_NAME: SomeClass::removeFromList
bool __thiscall SomeClass::removeFromList(int this, int param_2)
{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  int local_8;
  undefined4 local_4;
  
  // If param_2 is null, use 0 as the list node; otherwise offset by 0x48 (likely a node offset in a linked list)
  if (param_2 == 0) {
    local_8 = 0;
  }
  else {
    local_8 = param_2 + 0x48; // +0x48: offset to node pointer within object
  }
  
  // Initialize local_4 to 0
  local_4 = 0;
  
  // If the node is not null, set up a circular linked list by storing the address of local_8 into the node's next pointer
  if (local_8 != 0) {
    local_4 = *(undefined4 *)(local_8 + 4); // +0x04: next pointer in node
    *(int **)(local_8 + 4) = &local_8; // Set next to point to itself (circular)
  }
  
  // Search for the node in the list stored at this+0x94 (array of pairs)
  uVar1 = 0;
  uVar3 = 0xffffffff;
  if (*(uint *)(this + 0x98) != 0) { // +0x98: count of entries in the list
    piVar2 = *(int **)(this + 0x94); // +0x94: pointer to array of (node, something) pairs
    do {
      uVar3 = uVar1;
      if (*piVar2 == local_8) break; // Found matching node
      uVar1 = uVar1 + 1;
      piVar2 = piVar2 + 2; // Each entry is 2 ints (8 bytes)
      uVar3 = 0xffffffff;
    } while (uVar1 < *(uint *)(this + 0x98));
  }
  
  // If the node was not null, call a cleanup function on it
  if (local_8 != 0) {
    FUN_004daf90(&local_8); // Likely a destructor or cleanup function
  }
  
  // Return true if the node was found in the list (uVar3 != 0xffffffff)
  return uVar3 != 0xffffffff;
}