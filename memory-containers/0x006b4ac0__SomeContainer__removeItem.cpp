// FUNC_NAME: SomeContainer::removeItem
void __thiscall SomeContainer::removeItem(int this, int item)
{
  uint index;
  int *listPtr;
  int node;
  undefined4 local_4;
  
  // If item is null, node is 0; otherwise node = item + 0x48 (likely offset to a list node)
  if (item == 0) {
    node = 0;
  }
  else {
    node = item + 0x48;
  }
  
  // Initialize local_4 to 0
  local_4 = 0;
  
  // If node is not null, set up a linked list pointer (likely for removal)
  if (node != 0) {
    local_4 = *(undefined4 *)(node + 4);  // Save next pointer
    *(int **)(node + 4) = &node;          // Point next to itself (unlink?)
  }
  
  // Search for node in the container's array at this+0xf0 (count at this+0xf4)
  index = 0;
  if (*(uint *)(this + 0xf4) != 0) {
    listPtr = *(int **)(this + 0xf0);
    do {
      if (*listPtr == node) {
        if (index != 0xffffffff) goto LAB_006b4b33;  // Found, skip removal
        break;
      }
      index = index + 1;
      listPtr = listPtr + 2;  // Each entry is 8 bytes (likely pointer + something)
    } while (index < *(uint *)(this + 0xf4));
  }
  
  // If not found, call FUN_006b44e0 (likely a removal/cleanup function)
  FUN_006b44e0(&node);
  
LAB_006b4b33:
  // If node is not null, call FUN_004daf90 (likely a destructor or cleanup)
  if (node != 0) {
    FUN_004daf90(&node);
  }
  
  return;
}