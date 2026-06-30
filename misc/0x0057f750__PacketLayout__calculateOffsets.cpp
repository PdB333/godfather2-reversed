// FUNC_NAME: PacketLayout::calculateOffsets
void __thiscall PacketLayout::calculateOffsets(int thisPtr, uint baseOffset)
{
  int iVar1;
  
  // Align baseOffset to 16-byte boundary if not already
  if ((baseOffset & 0xf) != 0) {
    baseOffset = (baseOffset & 0xfffffff0) + 0x10;
  }
  
  // +0x6c: offset for first chunk (chunk type 0)
  *(undefined4 *)(thisPtr + 0x6c) = 0;
  if (*(short *)(thisPtr + 0x2a) != 0) {
    iVar1 = *(short *)(thisPtr + 0x2a) + -1;
    *(uint *)(thisPtr + 0x6c) = baseOffset;
    // Each chunk has 8-byte header + (count rounded up to 32) * 8 bytes
    baseOffset = baseOffset + 8 + ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) * 8;
  }
  
  // +0x74: offset for second chunk (chunk type 1)
  *(undefined4 *)(thisPtr + 0x74) = 0;
  if (*(short *)(thisPtr + 0x32) != 0) {
    iVar1 = *(short *)(thisPtr + 0x32) + -1;
    *(uint *)(thisPtr + 0x74) = baseOffset;
    baseOffset = baseOffset + 8 + ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) * 8;
  }
  
  // +0x70: offset for third chunk (chunk type 2)
  *(undefined4 *)(thisPtr + 0x70) = 0;
  if (*(short *)(thisPtr + 0x34) != 0) {
    iVar1 = *(short *)(thisPtr + 0x34) + -1;
    *(uint *)(thisPtr + 0x70) = baseOffset;
    baseOffset = baseOffset + 8 + ((int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5) * 8;
  }
  
  // +0x3a: raw data size (byte count)
  baseOffset = baseOffset + (int)*(short *)(thisPtr + 0x3a);
  
  // +0x50: offset for data block 0 (size at +0x4)
  *(undefined4 *)(thisPtr + 0x50) = 0;
  if (*(int *)(thisPtr + 4) != 0) {
    *(uint *)(thisPtr + 0x50) = baseOffset;
    baseOffset = baseOffset + *(int *)(thisPtr + 4);
  }
  
  // +0x4c: offset for data block 1 (size at +0x14)
  *(undefined4 *)(thisPtr + 0x4c) = 0;
  if (*(int *)(thisPtr + 0x14) != 0) {
    *(uint *)(thisPtr + 0x4c) = baseOffset;
    baseOffset = baseOffset + *(int *)(thisPtr + 0x14);
  }
  
  // +0x54: offset for data block 2 (size at +0x8)
  *(undefined4 *)(thisPtr + 0x54) = 0;
  if (*(int *)(thisPtr + 8) != 0) {
    *(uint *)(thisPtr + 0x54) = baseOffset;
    baseOffset = baseOffset + *(int *)(thisPtr + 8);
  }
  
  // +0x5c: offset for data block 3 (size at +0x20, ushort)
  *(undefined4 *)(thisPtr + 0x5c) = 0;
  if (*(ushort *)(thisPtr + 0x20) != 0) {
    *(uint *)(thisPtr + 0x5c) = baseOffset;
    baseOffset = baseOffset + *(ushort *)(thisPtr + 0x20);
  }
  
  // +0x60: offset for data block 4 (size at +0x22, ushort)
  *(undefined4 *)(thisPtr + 0x60) = 0;
  if (*(ushort *)(thisPtr + 0x22) != 0) {
    *(uint *)(thisPtr + 0x60) = baseOffset;
    baseOffset = baseOffset + *(ushort *)(thisPtr + 0x22);
  }
  
  // +0x58: offset for data block 5 (size at +0xc)
  *(undefined4 *)(thisPtr + 0x58) = 0;
  if (*(int *)(thisPtr + 0xc) != 0) {
    *(uint *)(thisPtr + 0x58) = baseOffset;
    baseOffset = baseOffset + *(int *)(thisPtr + 0xc);
  }
  
  // +0x64: offset for data block 6 (size at +0x1c, ushort)
  *(undefined4 *)(thisPtr + 100) = 0;
  if (*(ushort *)(thisPtr + 0x1c) != 0) {
    *(uint *)(thisPtr + 100) = baseOffset;
    baseOffset = baseOffset + *(ushort *)(thisPtr + 0x1c);
  }
  
  // +0x68: offset for data block 7 (size at +0x1e, ushort)
  *(undefined4 *)(thisPtr + 0x68) = 0;
  if (*(ushort *)(thisPtr + 0x1e) != 0) {
    *(uint *)(thisPtr + 0x68) = baseOffset;
    baseOffset = baseOffset + *(ushort *)(thisPtr + 0x1e);
  }
  
  // +0x26: if there's a ghost list, set up ghost offsets
  if (*(ushort *)(thisPtr + 0x26) != 0) {
    *(uint *)(thisPtr + 0x7c) = baseOffset;
    iVar1 = baseOffset + *(ushort *)(thisPtr + 0x26);
    *(int *)(thisPtr + 0x78) = iVar1;
    // +0x44: ghost data offset - conditional on +0x2e flag
    *(uint *)(thisPtr + 0x44) =
         -(uint)(*(short *)(thisPtr + 0x2e) != 0) & iVar1 + (uint)*(ushort *)(thisPtr + 0x28) * 4;
    return;
  }
  
  // No ghost list - clear ghost offsets
  *(undefined4 *)(thisPtr + 0x7c) = 0;
  *(undefined4 *)(thisPtr + 0x78) = 0;
  // +0x44: final offset - conditional on +0x2e flag
  *(uint *)(thisPtr + 0x44) = -(uint)(*(short *)(thisPtr + 0x2e) != 0) & baseOffset;
  return;
}