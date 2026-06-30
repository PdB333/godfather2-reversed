// FUNC_NAME: NetReadDecompressPacketHeader
undefined4 NetReadDecompressPacketHeader(undefined4 *compressedHeader, undefined4 *second32, uint *type, uint *timestampOrAck)
{
  int iVar1;
  int *buffer;
  size_t copySize;
  uint uVar2;
  undefined4 headerLocal;
  undefined4 secondLocal;
  uint localFlags;
  
  if (*buffer == 1) {
    iVar1 = buffer[3]; // +0x0C: read position in compressed data
    copySize = 0xc;
    if ((uint)(buffer[4] - iVar1) < 0xc) { // +0x10: compressed data size
      copySize = buffer[4] - iVar1;
    }
    _memcpy(&headerLocal, (void *)(buffer[5] + iVar1), copySize); // +0x14: compressed data pointer
    buffer[3] = iVar1 + copySize;
  }
  else {
    if (*buffer != 2) {
      return 0;
    }
    // For type 2, read via a function pointer
    copySize = (*(code *)buffer[4])(buffer[7], &headerLocal, 0xc); // +0x10: read function, +0x1C: reader context
  }
  if (copySize != 0xc) {
    return 0;
  }
  // Decompress header: first 16 bits of lower word are flags, rest is timestamp/sequence
  if ((localFlags & 0xffff0000) == 0) {
    uVar2 = localFlags << 8;
    localFlags = 0;
  }
  else {
    uVar2 = (localFlags >> 0xe & 0x3ff00) + 0x30000 | localFlags >> 0x10 & 0x3f;
    localFlags = localFlags & 0xffff;
  }
  if (compressedHeader != (undefined4 *)0x0) {
    *compressedHeader = headerLocal;
  }
  if (second32 != (undefined4 *)0x0) {
    *second32 = secondLocal;
  }
  if (timestampOrAck != (uint *)0x0) {
    *timestampOrAck = localFlags;
  }
  if (type != (uint *)0x0) {
    *type = uVar2;
  }
  return 1;
}