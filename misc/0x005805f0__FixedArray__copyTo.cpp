// FUNC_NAME: FixedArray::copyTo
struct ArrayBufferHeader {
    uint32_t unknown0;     // +0x00 (set to 0)
    uint32_t unknown4;     // +0x04 (set to 0)
    uint8_t flags;         // +0x08 (set to 1, meaning "owns data"?)
    uint8_t padding;       // +0x09 (0)
    uint16_t maxElements;  // +0x0A
    uint32_t elementCount; // +0x0C
    // uint8_t data[];     // +0x10 (each element 16 bytes)
};

// __thiscall: this in ecx, capacity in first param, outputBuffer in eax (hidden)
int __thiscall FixedArray::copyTo(uint32_t capacity, ArrayBufferHeader* outBuffer) {
    // this->+0x0A: max element count (ushort)
    // this->+0x0C: current element count (uint32)
    // this->+0x10: start of element array (each 16 bytes)
    
    if (*(uint16_t*)(this + 0x0A) <= capacity) {
        // Fill output buffer header
        outBuffer->unknown0 = 0;
        outBuffer->unknown4 = 0;
        outBuffer->flags = 1;      // +0x08
        outBuffer->padding = 0;    // +0x09
        outBuffer->maxElements = *(uint16_t*)(this + 0x0A);
        outBuffer->elementCount = *(uint32_t*)(this + 0x0C);
        
        uint32_t count = outBuffer->elementCount;
        uint32_t dataSize = count << 4; // each element 16 bytes
        memcpy(outBuffer + 4, (void*)(this + 0x10), dataSize);
        return 1;
    }
    return 0;
}