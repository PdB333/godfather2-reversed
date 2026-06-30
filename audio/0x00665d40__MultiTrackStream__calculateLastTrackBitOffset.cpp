// FUNC_NAME: MultiTrackStream::calculateLastTrackBitOffset
int __fastcall MultiTrackStream::calculateLastTrackBitOffset(void* thisUnused, int* descriptor)
{
  // descriptor structure:
  // +0x00: int trackCount
  // +0x04: ? (unused?)
  // +0x08: ? (unused?)
  // +0x0C: uint* trackSizes (array of bit sizes? or values whose bit length is used)
  int trackCount = *descriptor;
  if (trackCount != 0) {
    // Compute bit offset assuming each previous track uses 28 bits (header?)
    int bitOffset = (trackCount - 1) * 28;
    // Get the last track's size value (interpreted as bit length when shifted)
    uint lastTrackSize = *(uint *)(descriptor[3] + (trackCount - 1) * 4);
    // Count bits needed to represent lastTrackSize (floor(log2(value)) + 1)
    while (lastTrackSize != 0) {
      bitOffset++;
      lastTrackSize >>= 1;
    }
    return bitOffset;
  }
  return 0;
}