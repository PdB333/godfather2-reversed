// FUNC_NAME: NodeList::setHead
void __thiscall NodeList::setHead(int this, int node)
{
  int *headPtr; // pointer to head field at +0xEC
  
  headPtr = (int *)(this + 0xec);
  // If node is non-null, adjust to point to the embedded list node (offset +0x48)
  if (node != 0) {
    node = node + 0x48;
  }
  // Only change if the new node differs from current head
  if (*headPtr != node) {
    // Remove old head from its current list (if any)
    if (*headPtr != 0) {
      FUN_004daf90(headPtr); // likely unlinks node pointed by *headPtr
    }
    // Set new head
    *headPtr = node;
    if (node != 0) {
      // Save old next pointer of the new node into +0xF0 (prev pointer holder?)
      *(int *)(this + 0xf0) = *(int *)(node + 4);
      // Set the node's pprev (pointer to pointer that points to it) to the head field
      *(int **)(node + 4) = headPtr;
    }
  }
}