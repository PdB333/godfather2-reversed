//FUNC_NAME: PacketBuffer::writeQWords
int __thiscall PacketBuffer::writeQWords(void *this, int count)
{
  int *bufferEnd; // pointer to end of buffer? +0x14
  int *currentPtr; // pointer to current write position? +0x8
  int *writePtr; // temporary
  int i;
  int *src;
  int *dst;

  bufferEnd = *(int **)((int)this + 0x14); // +0x14: pointer to end of allocated buffer
  currentPtr = bufferEnd; // initially same as bufferEnd? Actually iVar2 = *(int *)(unaff_ESI + 0x14); iVar3 = iVar2;
  if (*(short *)((int)this + 0x2e) != 0) { // +0x2e: some flag (maybe "needsFlush")
    flushBuffer(); // FUN_00633920 - likely sends/flushes current packet
    currentPtr = extraout_EDX; // updated after flush
  }
  if ((*(byte *)((int)currentPtr + 8) & 1) != 0) { // check flag at currentPtr+8 (maybe "isFull" or "overflow")
    if ((*(byte *)((int)currentPtr + -0x10) & 1) != 0) { // check another flag at currentPtr-0x10
      flushBuffer();
      currentPtr = extraout_EDX_00;
    }
    // Check if there is enough space for 'count' QWords (8 bytes each)
    if (*(unsigned int *)((int)this + 0xc) < (unsigned int)(*(int *)((int)this + 8) + count * -8)) {
      // Copy 'count' QWords from source (at this+8 + count*-8) to destination (at this+0xc)
      i = 0;
      if (0 < count) {
        src = (int *)(*(int *)((int)this + 8) + count * -8);
        dst = (int *)(*(int *)((int)this + 0xc) + i * 8);
        do {
          *dst = *src;
          dst[1] = *(int *)((int)src + 4);
          i++;
          src += 2; // advance by 8 bytes (2 ints)
          dst += 2;
        } while (i < count);
      }
      // Update write pointer to new position
      *(int *)((int)this + 8) = *(int *)((int)this + 0xc) + count * 8;
    }
  }
  // Set a flag at currentPtr+8 (bit 4)
  *(unsigned int *)((int)currentPtr + 8) |= 0x10;
  return -1;
}