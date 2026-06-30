// FUNC_NAME: StreamBuffer::writeBlock(uint64_t header, const void* fixedData, size_t fixedSize, size_t varSize, int alignment, const void* varData)
void StreamBuffer::writeBlock(uint64_t header, const void* fixedData, size_t fixedSize, size_t varSize, int alignment, const void* varData) {
    // Get current write pointer from offset +0x14
    int* ptr = *(int**)(this + 0x14);
    
    // Align to 4 bytes before writing header
    ptr = (int*)(((uint32_t)ptr + 3) & 0xFFFFFFFC);
    *(uint64_t*)ptr = header;
    *(int**)(this + 0x14) = ptr;  // Save aligned pointer back? Actually not needed yet
    
    // After writing 8-byte header, align to next 4-byte boundary: (ptr + 8 + 3) & ~3 = (ptr + 11) & ~3
    ptr = (int*)((uint32_t)ptr + 11) & 0xFFFFFFFC);
    *(int**)(this + 0x14) = ptr;
    
    // Copy fixed size block (always 0x40 bytes from stack parameter)
    _memcpy(ptr, fixedData, 0x40);
    
    // Advance pointer by 0x40 bytes
    *(int*)(this + 0x14) = (int)((uint8_t*)ptr + 0x40);
    
    // Write variable size as 4 bytes
    **(size_t**)(this + 0x14) = varSize;
    *(int*)(this + 0x14) += 4;
    
    // Write alignment value as 4 bytes
    **(int**)(this + 0x14) = alignment;
    *(int*)(this + 0x14) += 4;
    
    // Align pointer to given alignment (power of two)
    uint32_t current = *(int*)(this + 0x14);
    uint32_t aligned = (current + 3 + alignment) & ~(alignment - 1);
    *(void**)(this + 0x14) = (void*)aligned;
    
    // Copy variable data
    _memcpy((void*)aligned, varData, varSize);
    
    // Advance and align to 4-byte boundary at the end
    uint32_t final = aligned + (uint32_t)varSize;
    final = (final + 3) & 0xFFFFFFFC;  // align to 4
    *(int*)(this + 0x14) = final;
}