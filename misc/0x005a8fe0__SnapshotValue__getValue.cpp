// FUNC_NAME: SnapshotValue::getValue
uint __fastcall SnapshotValue::getValue(uint *thisPtr)
{
  uint result;
  
  // Check if bit 15 is set (this is a float value flag)
  if ((~(byte)(*thisPtr >> 0xf) & 1) == 0) {
    // Switch on the value type (lower 15 bits)
    switch(*thisPtr & 0x7fff) {
    case 1:  // String type - parse as long
      result = _atol((char *)thisPtr[3]);
      return result;
    case 5:  // Unsigned integer
    case 7:  // Another integer type
      return thisPtr[1];
    case 6:  // Float - cast to int
      return (int)(float)thisPtr[1];
    }
  }
  return 0;
}