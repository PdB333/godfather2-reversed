// FUNC_NAME: SomeContainer::removeEntry
bool __thiscall SomeContainer::removeEntry(int this, int entry)
{
  uint index;
  int *entryPtr;
  uint foundIndex;
  int local_8;
  int local_4;
  
  // If entry is null, use 0 as the local pointer
  if (entry == 0) {
    local_8 = 0;
  }
  else {
    // Offset by 0x48 to get the actual entry pointer
    local_8 = entry + 0x48;
  }
  
  // Initialize local_4 to 0
  local_4 = 0;
  
  // If local_8 is not null, set up a linked list node
  if (local_8 != 0) {
    local_4 = *(int *)(local_8 + 4);  // Save next pointer
    *(int **)(local_8 + 4) = &local_8;  // Point back to itself (circular list?)
  }
  
  // Search for the entry in the container's array
  index = 0;
  foundIndex = 0xffffffff;
  if (*(uint *)(this + 0x110) != 0) {
    entryPtr = *(int **)(this + 0x10c);
    do {
      foundIndex = index;
      if (*entryPtr == local_8) break;
      index = index + 1;
      entryPtr = entryPtr + 2;
      foundIndex = 0xffffffff;
    } while (index < *(uint *)(this + 0x110));
  }
  
  // Clean up the local linked list node
  if (local_8 != 0) {
    FUN_004daf90(&local_8);  // Likely a list removal function
  }
  
  // Return true if entry was found (index >= 0)
  return (int)foundIndex >= 0;
}