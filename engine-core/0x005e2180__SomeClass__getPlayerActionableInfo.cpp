// FUNC_NAME: SomeClass::getPlayerActionableInfo
undefined4 __thiscall getPlayerActionableInfo(int this, undefined4 *outInfo)
{
  int in_EAX;
  undefined4 result;
  int i;
  int *currentEntry;
  undefined4 *src;
  
  result = 0;
  if (in_EAX != 0) {
    i = 0;
    currentEntry = (int *)(this + 0x490); // +0x490: start of player array (5 entries, each 0x4A4 bytes)
    while (in_EAX != *currentEntry) {
      i = i + 1;
      currentEntry = currentEntry + 0x129; // 0x129 * 4 = 0x4A4 bytes per entry
      if (4 < i) {
        return result;
      }
    }
    this = i * 0x4a4 + 4 + this; // +4: skip count? offset to found player's data block
    if (this != 0) {
      result = 1;
      src = (undefined4 *)(this + 0x210); // +0x210: offset to actionable info struct (0x1B * 4 = 0x6C bytes)
      for (i = 0x1b; i != 0; i = i + -1) {
        *outInfo = *src;
        src = src + 1;
        outInfo = outInfo + 1;
      }
    }
  }
  return result;
}