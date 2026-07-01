// FUNC_NAME: SomeClass::compareOrAssert
undefined4 __thiscall SomeClass::compareOrAssert(int *this, int *other)
{
  if ((*this == 0) || (*this != *other)) {
    FUN_00b97aea(); // likely assertion failure / crash handler
  }
  return CONCAT31((int3)((uint)this[1] >> 8), this[1] != other[1]);
}