// FUNC_NAME: SomeClass::compareSomeValues
undefined4 __thiscall SomeClass::compareSomeValues(int *this, int *other)
{
  // Check if the first fields are both non-null and equal
  if ((*this == 0) || (*this != *other)) {
    // If not, call an error/assert function
    FUN_00b97aea();
  }
  // Return a combined value: high byte of this[1] and a boolean for equality of this[1] and other[1]
  // +0x00: first field (pointer or int)
  // +0x04: second field (int)
  return CONCAT31((int3)((uint)this[1] >> 8), this[1] == other[1]);
}