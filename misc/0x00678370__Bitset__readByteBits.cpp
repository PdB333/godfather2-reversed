// FUNC_NAME: Bitset::readByteBits
uint __fastcall Bitset::readByteBits(undefined4 *thisPtr)
{
  byte bVar1;
  byte uVar2;
  uint in_EAX;

  // +0x00: pointer to current byte in bitstream
  // +0x04: remaining bits counter (0 or 1)
  if (*(short *)(thisPtr + 1) == 0) {
    // No bits remaining in current byte; read next byte, extract high nibble
    bVar1 = *(byte *)*thisPtr;
    *(undefined2 *)(thisPtr + 1) = 1;
    return (uint)(bVar1 >> 4);
  }
  // One bit remaining; consume the low nibble and advance byte pointer
  uVar2 = *(byte *)*thisPtr;
  *(undefined2 *)(thisPtr + 1) = 0;
  *thisPtr = (undefined1 *)*thisPtr + 1;
  return CONCAT31((int3)((uint)in_EAX >> 8), uVar2) & 0xffffff0f;
}