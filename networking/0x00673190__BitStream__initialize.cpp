// FUNC_NAME: BitStream::initialize
undefined4 * BitStream::initialize(int maxBits)

{
  undefined4 in_EAX;
  undefined4 *bitStream;
  int iVar2;
  
  bitStream = (undefined4 *)FUN_00673070(); // allocate memory for BitStream
  *bitStream = in_EAX; // +0x00: data pointer (from EAX, likely passed buffer)
  bitStream[2] = 0xffffffff; // +0x08: read position (initialized to -1)
  bitStream[1] = 0xffffffff; // +0x04: write position (initialized to -1)
  if (0x800 < maxBits) {
    maxBits = 0x800; // cap at 2048 bits (256 bytes)
  }
  bitStream[3] = (maxBits + 7 >> 3) * 2; // +0x0C: total buffer size in bytes (double for safety)
  iVar2 = FUN_00673070(); // allocate another buffer
  bitStream[4] = iVar2; // +0x10: secondary buffer pointer
  bitStream[5] = ((int)bitStream[3] >> 1) + iVar2; // +0x14: midpoint of secondary buffer
  return bitStream;
}