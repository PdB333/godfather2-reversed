// FUNC_NAME: SomeManager::processPendingItems
void __fastcall SomeManager::processPendingItems(int this)
{
  int originalCount;
  int i;
  int item;
  char result;
  int someObj;
  
  originalCount = *(int *)(this + 0xb8); // +0xB8: count of pending items
  i = originalCount;
  while (i = i + -1, -1 < i) {
    item = *(int *)(*(int *)(this + 0xb4) + i * 4); // +0xB4: array of pending item pointers
    result = FUN_00791230(); // some check function
    if (result == '\0') {
      someObj = FUN_00791300(); // get some object
      if ((someObj != 0) && (*(int *)(someObj + 0x158) == 0)) { // +0x158: some flag
        *(undefined1 **)(someObj + 0x158) = &LAB_006b2cc0; // set function pointer
      }
    }
    else {
      if (i != *(int *)(this + 0xb8) + -1) {
        // Remove item by swapping with last
        *(int *)(*(int *)(this + 0xb4) + i * 4) =
             *(int *)(*(int *)(this + 0xb4) + -4 + *(int *)(this + 0xb8) * 4);
      }
      *(int *)(this + 0xb8) = *(int *)(this + 0xb8) + -1; // decrement count
      FUN_00790110(0); // some cleanup
      FUN_00791350(this); // process next
      FUN_00792d80(item); // destroy item
    }
  }
  if (*(int *)(this + 0xb8) != originalCount) {
    FUN_006b2f70(); // update state
    if ((((*(int *)(this + 0x88) == 0) && (*(int *)(this + 0xa0) == 0)) &&
        (*(int *)(this + 0xac) == 0)) && (*(int *)(this + 0xb8) == 0)) {
      FUN_004086d0(&DAT_0112a640); // disable something
      return;
    }
    FUN_00408680(&DAT_0112a640); // enable something
  }
  return;
}