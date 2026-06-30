// FUNC_NAME: PacketBuilder::commitBlock
// Function at 0x00626460: Finalizes a data block in a packet being built.
// Uses implicit this in ESI, and an integer parameter (bytesWritten) in EAX.
// Object layout:
//   +0x08: writePointer (int*) - current writing position in buffer
//   +0x10: headerPointer (int*) - points to packet header structure
// Header structure at headerPointer:
//   +0x20: currentSize (uint)
//   +0x24: maxSize (uint)
void PacketBuilder::commitBlock(int bytesWritten)
{
  int *headerPtr = *(int **)(this + 0x10);
  uint currentSize = *(uint *)(headerPtr + 0x20);
  uint maxSize = *(uint *)(headerPtr + 0x24);

  // If buffer is about to overflow, flush/send current packet
  if (currentSize <= maxSize) {
    flushPacket(); // FUN_00627360 - sends current packet contents
  }

  if (bytesWritten > 1) {
    // Overflow or error: undo the write by adjusting pointer backward
    handleOverflow(); // FUN_006343b0 - maybe resets state
    int *writePos = *(int **)(this + 8);
    // Move write pointer back by (bytesWritten * 8 - 8) bytes (i.e., subtract bytesWritten*8 then add 8)
    writePos = writePos + (bytesWritten * -8 + 8) / sizeof(int);
    *(int **)(this + 8) = writePos;
    return;
  }

  if (bytesWritten == 0) {
    // Normal case: write a block header (type=4) and a sequence number
    int *writePos = *(int **)(this + 8);
    *writePos = 4;                         // Block type identifier (4 = ?)
    unsigned int seq = getNextSequence(); // FUN_00638920 - returns sequence number
    *(writePos + 1) = seq;
    // Advance write pointer by 8 bytes (2 ints)
    *(int **)(this + 8) = writePos + 2;
  }
  // If bytesWritten == 1? Unlikely; ignored (probably error case covered elsewhere)
}