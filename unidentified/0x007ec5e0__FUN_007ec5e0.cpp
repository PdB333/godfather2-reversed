// FUNC_NAME: SomeClass::compareOrAssert
undefined4 __thiscall SomeClass::compareOrAssert(int *this, int *other)
{
  if ((*this == 0) || (*this != *other)) {
    FUN_00b97aea(); // likely an assertion failure or error handler
  }
  // Compare the second field (byte at offset 4) and return a combined result:
  // - The high byte of the return value is the high byte of this->field1 (shifted right by 8)
  // - The low byte indicates whether this->field1 == other->field1 (1 if equal, 0 otherwise)
  return CONCAT31((int3)((uint)this[1] >> 8), this[1] == other[1]);
}