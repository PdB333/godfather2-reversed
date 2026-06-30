// FUNC_NAME: Bitfield::testFlag
uint Bitfield::testFlag(int *this, uint flag)
{
  char result;
  uint outValue;

  outValue = 0;
  result = (**(code **)(*this + 0x10))(flag, &outValue); // vtable call to get flag value
  return -(uint)(result != '\0') & flag; // return flag if set, else 0
}