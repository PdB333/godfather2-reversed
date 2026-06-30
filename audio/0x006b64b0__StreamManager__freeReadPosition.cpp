// FUNC_NAME: StreamManager::freeReadPosition
void __thiscall StreamManager::freeReadPosition(StreamDataRecord* this, uint bytesToFree)
{
  uint availData;
  uint consumedPrev;

  if (*(uint*)(this + 0x60) < *(uint*)(this + 0x5c)) {
    availData = *(uint*)(this + 0x5c) - *(uint*)(this + 0x60);
    if (bytesToFree < availData) {
      availData = bytesToFree;
    }
    consumedPrev = *(uint*)(this + 0x74);
    *(int*)(this + 0x58) = *(int*)(this + 0x58) - availData;  // -0x58: totalBufferOffset
    uint consumedNow = consumedPrev;
    if (availData <= consumedPrev) {
      consumedNow = availData;
    }
    uint consumedMin = consumedNow;
    if (consumedPrev < consumedNow) {
      consumedMin = consumedPrev;
    }
    *(uint*)(this + 0x74) = consumedPrev - consumedMin;  // -0x74: consumedBytes
    FUN_006b2f70();  // unknown helper
    for (int i = availData - consumedNow; i != 0; i--) {
      FUN_006b5c50(0);  // unknown helper
    }
  }
  if (bytesToFree <= *(uint*)(this + 0x5c)) {
    *(uint*)(this + 0x5c) = *(uint*)(this + 0x5c) - bytesToFree;  // -0x5c: readPosition
  }
  if (*(uint*)(this + 0x5c) < *(uint*)(this + 0x60)) {
    availData = *(uint*)(this + 0x68);  // -0x68: some limit
    uint base = *(uint*)(this + 0x6c);  // -0x6c: some base
    if (base < availData) {
      consumedPrev = availData - base;
    } else {
      consumedPrev = 0;
    }
    consumedMin = *(uint*)(this + 0x60) - *(uint*)(this + 0x5c);  // -0x60: writePosition?
    if (consumedMin < base) {
      consumedMin = base;
    }
    *(uint*)(this + 0x6c) = consumedMin;
    if (consumedMin < availData) {
      availData = availData - consumedMin;
    } else {
      availData = 0;
    }
    if (availData < consumedPrev) {
      FUN_008c78b0(*(uint*)(this + 0x40), consumedPrev - availData);  // -0x40: buffer, some mem func
    }
  }
  *(uint*)(this + 0x34) = *(uint*)(this + 0x34) & 0xf7ffffff;  // -0x34: flags, clear bit 27
}