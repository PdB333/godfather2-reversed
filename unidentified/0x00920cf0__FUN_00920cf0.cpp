// FUNC_NAME: SomeContainer::destroyAll
void __fastcall SomeContainer::destroyAll(int *this)
{
  int count;
  
  count = this[1];
  while (count = count + -1, -1 < count) {
    if (*(int *)(*this + count * 8) != 0) {
      FUN_004daf90(*this + count * 8); // destroy element at index count
    }
  }
  if (*this != 0) {
    FUN_009c8f10(*this); // free the array buffer
  }
  return;
}