// FUNC_NAME: TNLBitStream::readNextSegment
uint* __thiscall TNLBitStream::readNextSegment(int this, uint* outData, uint* sizePtr, int owner, int buffer)
{
  char cVar1;
  uint* puVar2;
  bool bVar3;
  int local_c;
  int local_8;

  // +0x20: mStopped flag (if non-zero, stream is dead)
  if (*(int*)(this + 0x20) == 0) {
    FUN_005e0510(this, outData, 1, sizePtr);
    return outData;
  }

  // +0x1c: mCurrentBuffer pointer (pointer to the active buffer description)
  local_8 = **(int**)(this + 0x1c);

  // Validate owner (assert if null or mismatch)
  if ((owner == 0) || (owner != this)) {
    FUN_00b97aea(); // _ASSERTE(owner == this)
  }

  // Case: buffer is the current buffer
  if (buffer == local_8) {
    // +0x0c: size field in buffer descriptor
    if (*sizePtr < *(uint*)(buffer + 0xc)) {
      FUN_005e0510(this, outData, 1, sizePtr);
      return outData;
    }
  }
  else {
    // Reload current buffer pointer (may have changed)
    local_8 = *(int*)(this + 0x1c);
    if ((owner == 0) || (owner != this)) {
      FUN_00b97aea();
    }
    if (buffer == local_8) {
      // Check the buffer at offset 0x1c, then offset 8, then offset 0x0c for size
      if (*(uint*)(*(int*)(*(int*)(this + 0x1c) + 8) + 0xc) < *sizePtr) {
        FUN_005e0510(this, outData, 0, sizePtr);
        return outData;
      }
    }
    else {
      // Buffer is not the current one; check sizes and possibly request more
      bVar3 = *(uint*)(buffer + 0xc) < *sizePtr;
      if (*sizePtr < *(uint*)(buffer + 0xc)) {
        FUN_005e1540(); // maybe wrap or seek
        if (*(uint*)(buffer + 0xc) < *sizePtr) {
          // +0x15 in buffer+8: some flag indicating "readable"?
          if (*(char*)(*(int*)(buffer + 8) + 0x15) == '\0') {
            FUN_005e0510(this, outData, 1, sizePtr);
            return outData;
          }
          FUN_005e0510(this, outData, 0, sizePtr);
          return outData;
        }
        bVar3 = *(uint*)(buffer + 0xc) < *sizePtr;
      }
      if (bVar3) {
        local_8 = *(int*)(this + 0x1c);
        local_c = this;
        FUN_005e15c0(); // maybe reallocate or advance
        cVar1 = FUN_005dff60(); // check if enough data now
        if ((cVar1 != '\0') || (*sizePtr < *(uint*)(buffer + 0xc))) {
          if (*(char*)(*(int*)(buffer + 8) + 0x15) == '\0') {
            FUN_005e0510(this, outData, 1, sizePtr);
            return outData;
          }
          FUN_005e0510(this, outData, 0, sizePtr);
          return outData;
        }
      }
    }
  }

  // Read the actual data from the buffer into outData
  puVar2 = (uint*)FUN_005e0330(this, &local_c, sizePtr);
  *outData = *puVar2;
  outData[1] = puVar2[1];
  return outData;
}