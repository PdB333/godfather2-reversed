// FUNC_NAME: SomeContainer::clear
void __fastcall SomeContainer::clear(int *this)
{
  int numItems;
  
  numItems = this[1];
  while (numItems = numItems + -1, -1 < numItems) {
    if (*(int *)(*this + numItems * 8) != 0) {
      FUN_004daf90(*this + numItems * 8);
    }
  }
  if (*this != 0) {
    FUN_009c8f10(*this);
  }
  return;
}