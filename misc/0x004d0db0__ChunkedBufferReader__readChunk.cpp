// FUNC_NAME: ChunkedBufferReader::readChunk
int __thiscall ChunkedBufferReader::readChunk(int this, int* chunkHeader)
{
  // chunkHeader points to a 4-byte magic, then size? fields.
  int magic = *chunkHeader;
  int type;
  int chunkSize;
  int result;
  int remaining;
  int newOffset;
  void* buffer;
  int* allocBuffer;

  // Check magic: must be "COHS" (little-endian 0x53484F43), not "FILL" (0x46494C4C)
  if ((magic != 0x46494c4c) && (magic == 0x53484f43)) {
    type = chunkHeader[2];  // chunk type at offset 8
    if (type == 0x5270616b) { // "Rpak" (little-endian)
      // Check if bit 0 of flags is clear (not processing)
      if ((*(uint8_t*)(this + 0xa8) & 1) == 0) {
        // Read data from chunk into buffer
        // buffer structure: [0]? , [4]? , [8] = data pointer, [0xc] = size
        void* bufferStruct = *(void**)(this + 0x108);
        char* dataPtr = *(char**)((int)bufferStruct + 8);
        int currentOffset = *(int*)(this + 0x10c);
        char* dest = dataPtr + currentOffset;
        // chunk data after header: chunkHeader + 4 (skip magic and type? Actually type is at offset 8, so data at +12)
        int* chunkData = chunkHeader + 3;
        int bytesRead = FUN_00b91d30(dest, chunkData); // copies from chunk data to buffer?
        *(int*)(this + 0x10c) = currentOffset + bytesRead;
        // Check if buffer is full
        if (*(int*)(this + 0x10c) == *(int*)((int)bufferStruct + 0xc)) {
          // Call handler's processBuffer method (vtable offset 0xc)
          (**(code**)(**(int**)(this + 0x94) + 0xc))(bufferStruct);
          FUN_004d0f80(bufferStruct); // free buffer structure
          *(void**)(this + 0x108) = 0;
          *(int*)(this + 0x10c) = 0;
        }
      }
    }
    else if (type == 0x53444154) { // "SDAT" (little-endian)
      if ((*(uint8_t*)(this + 0xa8) & 1) == 0) {
        void* bufferStruct = *(void**)(this + 0x108);
        int bufferSize = *(int*)((int)bufferStruct + 0xc);
        int currentOffset = *(int*)(this + 0x10c);
        int remainingSpace = bufferSize - currentOffset;
        chunkSize = chunkHeader[1] - 0xc; // payload size from header
        int copySize = (remainingSpace < chunkSize) ? remainingSpace : chunkSize;
        char* dest = *(char**)((int)bufferStruct + 8) + currentOffset;
        int* src = chunkHeader + 3;
        memcpy(dest, src, copySize);
        *(int*)(this + 0x10c) = currentOffset + copySize;
        if (*(int*)(this + 0x10c) == bufferSize) {
          (**(code**)(**(int**)(this + 0x94) + 0xc))(bufferStruct);
          FUN_004d0f80(bufferStruct);
          *(void**)(this + 0x108) = 0;
          *(int*)(this + 0x10c) = 0;
        }
      }
    }
    else if (type == 0x53484452) { // "SHDR" (little-endian)
      // If field at +0x10 is zero, return 0 (failure)
      if (*(int*)(this + 0x10) == 0) {
        return 0;
      }
      // Allocate buffer via handler's allocateBuffer method (vtable offset 4)
      allocBuffer = (int*)(**(code**)(**(int**)(this + 0x94) + 4))();
      // Check if allocation size (first int) is 1? Possibly indicating a small buffer?
      if (*allocBuffer == 1) {
        // Success: clear bit 0 of flags, store buffer
        *(uint*)(this + 0xa8) &= 0xfffffffe;
        *(int**)(this + 0x108) = allocBuffer;
      } else {
        // Failure: set bit 0, call processBuffer (to discard?), free
        *(uint*)(this + 0xa8) |= 1;
        (**(code**)(**(int**)(this + 0x94) + 0xc))(allocBuffer);
        FUN_004d0f80(allocBuffer);
        return 0; // return zero? (unaff_BL is undefined)
      }
    }
  }
  return 1; // processed successfully or ignored
}