// FUNC_NAME: StringTable::findOrAddString
uint StringTable::findOrAddString(uint *outHash, int stringIndex)
{
  uint hash = in_EAX & 0xffffff00;
  int foundIndex = 0;
  uint currentSlot = 0;
  
  if (*(byte *)(unaff_EDI + 0x1c) != 0) { // +0x1c: stringCount
    while (true) {
      int slotIndex = foundIndex;
      if (*(char *)(unaff_EDI + 0x18 + currentSlot) != '\0' && // +0x18: stringTable
          stringIndex == foundIndex) {
        break;
      }
      currentSlot++;
      foundIndex = slotIndex;
      if ((int)(uint)*(byte *)(unaff_EDI + 0x1c) <= (int)currentSlot) { // +0x1c: stringCount
        return hash;
      }
    }
    if ((byte)currentSlot < 4) {
      hash = (currentSlot & 0xff) ^ 0xad103100;
      *outHash = hash;
    }
    hash = CONCAT31((int3)(hash >> 8), 1);
  }
  return hash;
}