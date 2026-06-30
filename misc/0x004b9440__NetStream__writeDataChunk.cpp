// FUNC_NAME: NetStream::writeDataChunk
// Address: 0x004b9440
// Role: Writes a chunk of data: four 32-bit header values, then an array of 12-byte structures.
// Offset +0x14: current write pointer (uint8_t*)

void NetStream::writeDataChunk(uint32_t header1, uint32_t header2, void* data, int count, uint32_t alignment) {
    // Write header fields
    *(uint32_t*)(*(uint32_t**)(this + 0x14)) = header1;
    *(uint32_t*)(this + 0x14) += 4;
    *(uint32_t*)(*(uint32_t**)(this + 0x14)) = header2;
    *(uint32_t*)(this + 0x14) += 4;
    *(int*)(*(uint32_t**)(this + 0x14)) = count;
    *(uint32_t*)(this + 0x14) += 4;
    *(uint32_t*)(*(uint32_t**)(this + 0x14)) = alignment;
    
    // Align write pointer to next multiple of alignment (with +3 offset as per original)
    uintptr_t currentPointer = *(uintptr_t*)(this + 0x14);
    uintptr_t alignedPointer = (~((uintptr_t)alignment - 1)) & (alignment + 3 + currentPointer);
    *(uintptr_t*)(this + 0x14) = alignedPointer;
    
    // Copy data array (each element is 12 bytes)
    memcpy((void*)alignedPointer, data, count * 12);
    
    // Advance pointer past copied data
    *(uintptr_t*)(this + 0x14) += count * 12;
}