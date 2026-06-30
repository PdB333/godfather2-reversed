// FUNC_NAME: Bitfield::testFlag
uint Bitfield::testFlag(int *this, uint flag)
{
  char result;
  uint local_4;

  local_4 = 0;
  // Call virtual function at vtable+0x10 to test if flag is set
  result = (**(code **)(*this + 0x10))(flag, &local_4);
  // Return flag if set, otherwise 0
  return -(uint)(result != '\0') & flag;
}