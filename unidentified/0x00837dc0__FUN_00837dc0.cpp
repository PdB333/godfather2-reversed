// FUNC_NAME: SomeClass::releaseChildrenAndSelf
void __fastcall SomeClass::releaseChildrenAndSelf(int *this)
{
  uint childIndex;
  int *child;

  childIndex = 0;
  if (this[9] != 0) { // +0x24: childCount
    do {
      child = *(int **)(this[8] + childIndex * 4); // +0x20: children array
      if (child != 0) {
        SomeClass::releaseChildrenAndSelf(child); // recursive call
        FUN_009c8eb0(child); // likely operator delete or release
      }
      childIndex = childIndex + 1;
    } while (childIndex < (uint)this[9]); // +0x24
  }
  if (this[8] != 0) { // +0x20: children array
    FUN_009c8f10(this[8]); // likely free or release array
  }
  if (this[5] != 0) { // +0x14: some other resource
    FUN_009c8f10(this[5]); // release
  }
  if (*this != 0) { // +0x00: vtable or object pointer
    (*(code *)this[3])(*this); // call destructor via vtable at +0x0C
  }
  return;
}