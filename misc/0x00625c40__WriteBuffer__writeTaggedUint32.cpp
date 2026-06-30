// FUNC_NAME: WriteBuffer::writeTaggedUint32
// Address: 0x00625c40
// This function writes a 4-byte tag (value 3) followed by a 4-byte value into a buffer,
// advancing the internal write pointer by 8 bytes. Used for constructing command streams
// or messages with a hardcoded opcode. The class at this+0x8 stores a pointer to the
// current write location in the buffer.

void WriteBuffer::writeTaggedUint32(uint32 value) {
    // +0x8: pointer to current write position in the buffer
    uint32* writePtr = *(uint32**)((uint8*)this + 8);
    
    // Write opcode/tag = 3
    *writePtr = 3;
    
    // Write the data value
    writePtr[1] = value;
    
    // Advance the stored write pointer by 8 bytes (two uint32 slots)
    *(uint32**)((uint8*)this + 8) = writePtr + 2;
}