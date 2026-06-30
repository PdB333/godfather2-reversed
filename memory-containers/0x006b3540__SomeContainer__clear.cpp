// FUNC_NAME: SomeContainer::clear
void __fastcall SomeContainer::clear(int *this)
{
  int count;
  
  count = this[1];
  while (count = count + -1, -1 < count) {
    if (*(int *)(*this + count * 8) != 0) {
      FUN_004daf90(*this + count * 8); // likely delete or release element at index
    }
  }
  if (*this != 0) {
    FUN_009c8f10(*this); // likely free the array buffer
  }
  return;
}