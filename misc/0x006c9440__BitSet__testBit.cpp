// FUNC_NAME: BitSet::testBit
uint BitSet::testBit(int *this, uint bitIndex)
{
  uint result;
  char byteValue;
  
  result = 0;
  // Call virtual function at vtable+0x10 to get byte at bitIndex/8, then test bitIndex%8
  byteValue = (**(code **)(*this + 0x10))(bitIndex, &result);
  // Return bitIndex if bit is set, otherwise 0
  return -(uint)(byteValue != '\0') & bitIndex;
}