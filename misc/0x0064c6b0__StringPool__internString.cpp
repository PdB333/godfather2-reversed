// FUNC_NAME: StringPool::internString
void __thiscall StringPool::internString(char *destString)
{
  byte bitValue;
  uint currentSlot;
  char *srcPtr;
  int diff;
  uint local_4;

  currentSlot = *(uint *)(this + 0x18);               // +0x18: currentSlot index (next free slot)
  if (*(uint *)(this + 0x2c) < currentSlot) {         // +0x2c: capacity (max slots)
    *(byte *)(this + 0x1c) = 1;                       // +0x1c: overflow flag
  }
  else {
    bitValue = *(byte *)((currentSlot >> 3) + *(int *)(this + 0xc)); // +0x0c: pointer to bitmap (bitset)
    *(uint *)(this + 0x18) = currentSlot + 1;         // Advance slot counter
    if ((bitValue & (byte)(1 << ((byte)currentSlot & 7))) != 0) {
      // Slot already occupied -> return existing string from pool
      local_4 = 0;
      FUN_0064b9e0(8, &local_4);                      // Gets random byte for offset?
      FUN_0065ae90((local_4 & 0xff) + 0x38 + this);   // Initialize string slot? (has side effects)
      srcPtr = (char *)(this + 0x38);                 // +0x38: start of string buffer
      diff = (int)destString - (int)srcPtr;           // Offset to output buffer
      // Copy from pool buffer to destString (output)
      do {
        char c = *srcPtr;
        srcPtr[diff] = c;
        srcPtr++;
      } while (c != '\0');
      return;
    }
  }
  // Slot free -> store incoming string in pool
  local_4 = (uint)this;                                // store this for later use?
  FUN_0065ae90(destString);                            // Might be strcpy or initialization
  diff = (int)(this + 0x38) - (int)destString;        // Offset from dest to pool buffer
  // Copy from destString to pool buffer
  do {
    char c = *destString;
    destString[diff] = c;
    destString++;
  } while (c != '\0');
  return;
}