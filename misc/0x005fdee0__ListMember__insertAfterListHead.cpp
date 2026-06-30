// FUNC_NAME: ListMember::insertAfterListHead

void __thiscall ListMember::insertAfterListHead(int this, int parentObj)
{
  int *nextPtr; // pointer to this->next (at +0x4c)
  int newNext; // address of the list anchor node (parentObj + 0x48)

  nextPtr = (int *)(this + 0x4c); // this->next
  if (parentObj == 0) {
    newNext = 0;
  }
  else {
    newNext = parentObj + 0x48; // anchor node is at parentObj + 0x48
  }
  if (*nextPtr != newNext) { // only relink if not already pointing there
    if (*nextPtr != 0) {
      // remove this node from current list
      FUN_004daf90(nextPtr);
    }
    *nextPtr = newNext; // this->next = anchor node address
    if (newNext != 0) {
      // set this->prev to the previous prev of the anchor
      *(int *)(this + 0x50) = *(int *)(newNext + 4);
      // set anchor's prev to point to this->next's address
      *(int **)(newNext + 4) = nextPtr;
    }
  }
  // mark node as attached/active
  *(int *)(this + 0xbc) = 2;
}