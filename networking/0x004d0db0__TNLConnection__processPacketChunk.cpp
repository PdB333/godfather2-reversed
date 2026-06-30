// FUNC_NAME: TNLConnection::processPacketChunk
undefined1 TNLConnection::processPacketChunk(int this)
{
  int *packetHeader;
  int *piVar1;
  uint uVar2;
  int chunkType;
  int unaff_ESI;
  uint copySize;
  undefined1 unaff_BL;
  undefined1 unaff_retaddr;
  
  // Check packet header magic: "FILL" or "CHOS" (chunked packet)
  if ((*packetHeader != 0x46494c4c) && (*packetHeader == 0x53484f43)) {
    chunkType = packetHeader[2];
    if (chunkType == 0x5270616b) { // "Rpak" - packet chunk header
      if ((*(byte *)(unaff_ESI + 0xa8) & 1) == 0) { // +0xa8: flags, bit0 = receiving
        // Copy chunk data into receive buffer
        int bytesCopied = FUN_00b91d30(*(int *)(*(int *)(unaff_ESI + 0x108) + 8) + *(int *)(unaff_ESI + 0x10c),
                             packetHeader + 4);
        *(int *)(unaff_ESI + 0x10c) = *(int *)(unaff_ESI + 0x10c) + bytesCopied; // +0x10c: receive offset
        if (*(int *)(unaff_ESI + 0x10c) == *(int *)(*(int *)(unaff_ESI + 0x108) + 0xc)) { // +0xc: buffer size
          // Complete packet received - notify via callback at +0x94
          (**(code **)(**(int **)(this + 0x94) + 0xc))(*(int *)(unaff_ESI + 0x108));
          FUN_004d0f80(*(undefined4 *)(unaff_ESI + 0x108)); // free buffer
          *(undefined4 *)(unaff_ESI + 0x108) = 0;
          *(undefined4 *)(unaff_ESI + 0x10c) = 0;
        }
      }
    }
    else if (chunkType == 0x53444154) { // "SDAT" - data chunk
      if ((*(byte *)(unaff_ESI + 0xa8) & 1) == 0) {
        uVar2 = *(int *)(*(int *)(unaff_ESI + 0x108) + 0xc) - *(int *)(unaff_ESI + 0x10c);
        copySize = packetHeader[1] - 0xcU; // chunk size minus header
        if (uVar2 <= packetHeader[1] - 0xcU) {
          copySize = uVar2;
        }
        _memcpy((void *)(*(int *)(*(int *)(unaff_ESI + 0x108) + 8) + *(int *)(unaff_ESI + 0x10c)),
                packetHeader + 3, copySize);
        *(int *)(unaff_ESI + 0x10c) = *(int *)(unaff_ESI + 0x10c) + copySize;
        if (*(int *)(unaff_ESI + 0x10c) == *(int *)(*(int *)(unaff_ESI + 0x108) + 0xc)) {
          (**(code **)(**(int **)(this + 0x94) + 0xc))(*(int *)(unaff_ESI + 0x108));
          FUN_004d0f80(*(undefined4 *)(unaff_ESI + 0x108));
          *(undefined4 *)(unaff_ESI + 0x108) = 0;
          *(undefined4 *)(unaff_ESI + 0x10c) = 0;
          return unaff_retaddr;
        }
      }
    }
    else if (chunkType == 0x53484452) { // "SHDR" - start header
      if (*(int *)(this + 0x10) == 0) { // +0x10: some state flag
        return 0;
      }
      piVar1 = (int *)(**(code **)(**(int **)(this + 0x94) + 4))(); // allocate buffer via callback
      if (*piVar1 == 1) {
        *(uint *)(unaff_ESI + 0xa8) = *(uint *)(unaff_ESI + 0xa8) & 0xfffffffe; // clear receiving flag
        *(int **)(unaff_ESI + 0x108) = piVar1; // +0x108: receive buffer
        return unaff_retaddr;
      }
      *(uint *)(unaff_ESI + 0xa8) = *(uint *)(unaff_ESI + 0xa8) | 1; // set receiving flag
      (**(code **)(**(int **)(this + 0x94) + 0xc))(piVar1); // notify completion
      FUN_004d0f80(piVar1); // free buffer
      return unaff_BL;
    }
  }
  return 1;
}