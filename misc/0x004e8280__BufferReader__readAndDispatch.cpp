// FUNC_NAME: BufferReader::readAndDispatch
typedef void (__cdecl *EventHandler)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

void BufferReader::readAndDispatch(void* this, EventHandler* handler) {
    // this+0x18 points to a buffer pointer (current read position)
    uint32_t** bufferPtr = (uint32_t**)((char*)this + 0x18);
    uint32_t* buffer = *bufferPtr;

    // Save the original value before alignment
    uint32_t originalValue = *buffer;

    // Align buffer pointer up to 4 bytes (typical alignment for packed data)
    uint32_t* alignedBuffer = (uint32_t*)(((uint32_t)buffer + 7) & 0xFFFFFFFC);
    *bufferPtr = alignedBuffer;

    // Copy 28 bytes (7 uint32) from aligned buffer into local stack variables
    uint32_t args[7];
    _memcpy(args, alignedBuffer, 0x1C);

    // Advance buffer pointer by 28 bytes
    *bufferPtr = (uint32_t*)((uint8_t*)alignedBuffer + 0x1C);

    // Read next 8 bytes as a 64-bit value
    uint64_t extra = *(uint64_t*)*bufferPtr;

    // Advance buffer pointer by 8 more bytes (total 0x24 from original aligned)
    *bufferPtr = (uint32_t*)((uint8_t*)alignedBuffer + 0x24);

    // Split 64-bit value into two 32-bit parts
    uint32_t extraLow = (uint32_t)(extra & 0xFFFFFFFF);
    uint32_t extraHigh = (uint32_t)(extra >> 32);

    // Call the handler with all extracted data
    (*handler)(originalValue, args[0], args[1], args[2], args[3], args[4], args[5], args[6], extraLow, extraHigh);
}