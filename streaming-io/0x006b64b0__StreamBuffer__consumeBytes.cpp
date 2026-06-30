// FUNC_NAME: StreamBuffer::consumeBytes
void __thiscall StreamBuffer::consumeBytes(uint bytesToConsume)
{
  uint available;
  uint chunkSize;
  uint clipped;
  uint extra;
  uint currentChunk;
  uint afterChunk;
  int i;

  // If there are bytes buffered (readPosition < writePosition)
  if (this->readPosition < this->writePosition) {
    available = this->writePosition - this->readPosition;
    if (bytesToConsume < available) {
      available = bytesToConsume;
    }
    currentChunk = this->currentChunkSize;   // +0x74
    this->bytesAvailable -= available;       // +0x58
    clipped = currentChunk;
    if (available <= currentChunk) {
      clipped = available;
    }
    // Ensure clipped doesn't exceed currentChunkSize (redundant check)
    if (currentChunk < clipped) {
      clipped = currentChunk;
    }
    this->currentChunkSize = currentChunk - clipped;  // +0x74
    FUN_006b2f70(); // likely lock/beginTransaction
    for (i = available - clipped; i != 0; i--) {
      FUN_006b5c50(0); // consume a full chunk (e.g., skip to next segment)
    }
  }

  // Decrease writePosition if bytesToConsume is within bounds
  if (bytesToConsume <= this->writePosition) {
    this->writePosition -= bytesToConsume;   // +0x5c
  }

  // After consumption, check if buffer needs refill
  if (this->writePosition < this->readPosition) {
    // Compute freed space above next threshold
    uint lowMark = this->lowWaterMark;       // +0x6c
    uint highMark = this->highWaterMark;     // +0x68
    uint spaceAboveHigh = (lowMark < highMark) ? (highMark - lowMark) : 0;
    uint spaceFreed = this->readPosition - this->writePosition; // +0x60 - +0x5c
    if (spaceFreed < lowMark) {
      spaceFreed = lowMark;
    }
    this->lowWaterMark = spaceFreed;         // +0x6c
    uint spaceRemaining = (spaceFreed < highMark) ? (highMark - spaceFreed) : 0;
    if (spaceRemaining < spaceAboveHigh) {
      // Notify that a chunk of size (spaceAboveHigh - spaceRemaining) is available
      FUN_008c78b0(*(this->somePointer), spaceAboveHigh - spaceRemaining); // +0x40
    }
  }

  // Clear the "needs processing" flag (bit 27)
  this->flags &= ~0x08000000; // +0x34
}