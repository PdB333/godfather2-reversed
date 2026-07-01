// FUNC_NAME: EntityDataManager::getFloatAttribute
float __thiscall EntityDataManager::getFloatAttribute(undefined4 *this, int attributeId)
{
  int iVar1;
  int *piVar2;
  int count;
  float result;
  
  count = this[1]; // +0x04: number of attribute entries
  result = DAT_00d5ccf8; // default float value (likely 0.0f or -1.0f)
  if (count != 0) {
    piVar2 = (int *)*this; // +0x00: pointer to attribute array (3 ints per entry: id, type, value)
    while( true ) {
      if (*piVar2 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *piVar2 + -0x48; // offset to attribute ID (0x48 = 72, likely a hash or enum offset)
      }
      if (iVar1 == attributeId) break;
      count = count + -1;
      piVar2 = piVar2 + 3; // each entry is 12 bytes (3 ints)
      if (count == 0) {
        return (float10)DAT_00d5ccf8; // not found, return default
      }
    }
    result = (float)piVar2[2]; // +0x08: float value at entry index 2
  }
  return (float10)result;
}