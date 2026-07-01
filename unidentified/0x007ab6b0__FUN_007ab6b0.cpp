// FUNC_NAME: SomeClass::setSomePointer
void __thiscall SomeClass::setSomePointer(int this, int newPtr)
{
  int basePtr = *(int *)(this + 0x58); // +0x58: pointer to some sub-object
  int *targetSlot = (int *)(basePtr + 0x24fc); // +0x24fc: pointer slot to set

  if (newPtr == 0) {
    newPtr = 0;
  }
  else {
    newPtr = newPtr + 0x48; // offset to some field within the object
  }

  if (*targetSlot != newPtr) {
    if (*targetSlot != 0) {
      FUN_004daf90(targetSlot); // likely a destructor or release function
    }
    *targetSlot = newPtr;
    if (newPtr != 0) {
      *(int *)(basePtr + 0x2500) = *(int *)(newPtr + 4); // +0x2500: some other pointer
      *(int **)(newPtr + 4) = targetSlot; // set back-pointer to targetSlot
    }
  }
}