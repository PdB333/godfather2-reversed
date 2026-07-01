// FUNC_NAME: SomeArrayCleanupContainer::destroyAllElements
void __fastcall SomeArrayCleanupContainer::destroyAllElements(int *this)
{
  int remainingCount;
  
  remainingCount = this[1];  // +0x04 probably count/numElements
  while (remainingCount = remainingCount + -1, -1 < remainingCount) {
    if (*(int *)(*this + remainingCount * 8) != 0) {
      FUN_004daf90(*this + remainingCount * 8);  // destroy/release element at index
    }
  }
  if (*this != 0) {
    FUN_009c8f10(*this);  // free/deallocate the array buffer
  }
  return;
}