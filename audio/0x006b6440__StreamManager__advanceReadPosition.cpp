// FUNC_NAME: StreamManager::advanceReadPosition
void __thiscall StreamManager::advanceReadPosition(int this, int bytesToAdvance)

{
  uint currentPos;
  uint maxPos;
  
  currentPos = *(uint *)(this + 0x5c); // +0x5c: current read position in stream
  maxPos = *(uint *)(this + 0x60);      // +0x60: maximum read position (buffer size)
  if (*(uint *)(this + 0x60) <= currentPos) {
    maxPos = currentPos;
  }
  currentPos = currentPos + bytesToAdvance;
  *(uint *)(this + 0x5c) = currentPos; // update read position
  if (maxPos < currentPos) {
    // We've read past the previous max - update total bytes read and stream position
    *(int *)(this + 0x58) = *(int *)(this + 0x58) + (currentPos - maxPos); // +0x58: total bytes read
    *(int *)(this + 0x74) = *(int *)(this + 0x74) + (currentPos - maxPos); // +0x74: stream position offset
    if ((_DAT_00d577a0 < *(float *)(this + 0x80)) || // +0x80: some threshold float
       ((*(uint *)(this + 0x34) >> 0x1d & 1) != 0)) { // +0x34: flags, bit 29 = streaming flag
      StreamManager::requestMoreData(); // 0x6b2f70
    }
    else {
      StreamManager::processBufferedData(); // 0x6b59f0
    }
    if (*(int *)(this + 0x40) == 0x637b907) { // +0x40: stream type identifier
      *(undefined4 *)(this + 0x70) = DAT_01205224; // +0x70: some data pointer
      *(uint *)(this + 0x34) = *(uint *)(this + 0x34) | 0x8000000; // set bit 27
    }
  }
  return;
}