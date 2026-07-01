// FUNC_NAME: SomeClass::allocateAndLinkThreeObjects
void __fastcall SomeClass::allocateAndLinkThreeObjects(int this)
{
  int obj;
  int *slotPtr;
  int *otherSlotPtr;
  int prevObj;
  int i;

  slotPtr = (int *)(this + 0xcb4);
  i = 3;
  do {
    obj = FUN_005f7290(1); // allocate object of size 1? Or type ID 1?
    *slotPtr = obj;
    if (obj != 0) {
      FUN_005f7250(obj); // initialize object
      obj = *slotPtr;
      otherSlotPtr = (int *)(obj + 0x24); // +0x24: link field
      if (this == 0) {
        prevObj = 0;
      }
      else {
        prevObj = this + 0x48; // +0x48: head of linked list
      }
      if (*otherSlotPtr != prevObj) {
        if (*otherSlotPtr != 0) {
          FUN_004daf90(otherSlotPtr); // unlink from previous list
        }
        *otherSlotPtr = prevObj;
        if (prevObj != 0) {
          *(undefined4 *)(obj + 0x28) = *(undefined4 *)(prevObj + 4); // +0x28: next pointer
          *(int **)(prevObj + 4) = otherSlotPtr; // +4: prev pointer
        }
      }
    }
    slotPtr = slotPtr + 1;
    i = i + -1;
  } while (i != 0);
  return;
}