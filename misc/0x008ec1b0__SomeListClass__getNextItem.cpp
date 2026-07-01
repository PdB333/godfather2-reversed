// FUNC_NAME: SomeListClass::getNextItem
int __fastcall SomeListClass::getNextItem(int *this)
{
  if (*this == 0) {
    FUN_00b97aea(); // probably error/assert
  }
  if (this[1] == *(int *)(*this + 4)) {
    FUN_00b97aea(); // probably error/assert
  }
  return this[1] + 0xc;
}