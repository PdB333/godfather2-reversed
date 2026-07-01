// FUNC_NAME: GameDataBlock::assignFrom
undefined4 * __thiscall GameDataBlock::assignFrom(undefined4 *this, undefined4 *source)
{
  int iVar1;
  undefined4 *destIter;
  undefined4 *srcIter;
  
  // Copy first block: 16 dwords (64 bytes)
  destIter = source;
  srcIter = this;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *srcIter = *destIter;
    destIter = destIter + 1;
    srcIter = srcIter + 1;
  }
  
  // Copy second block: 64 dwords (256 bytes)
  destIter = source + 0x10;
  srcIter = this + 0x10;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *srcIter = *destIter;
    destIter = destIter + 1;
    srcIter = srcIter + 1;
  }
  
  // Copy two individual dwords at offset 0x50 and 0x51 (word offsets, i.e., bytes 0x140 and 0x144)
  this[0x50] = source[0x50];
  this[0x51] = source[0x51];
  
  // Copy 8 bytes at offset 0x52 and 0x54 (word offsets, i.e., bytes 0x148 and 0x150)
  *(undefined8 *)(this + 0x52) = *(undefined8 *)(source + 0x52);
  *(undefined8 *)(this + 0x54) = *(undefined8 *)(source + 0x54);
  
  // Call additional initialization on a sub-object at source offset 0x56 (word offset, i.e., byte 0x158)
  FUN_00acccf0(source + 0x56);
  
  return this;
}