// FUNC_NAME: PacketBuffer::processChunkType6
// Address: 0x006338a0
// This function handles a specific chunk type (6) in the packet buffer.
// It appears to be part of the packet serialization system (likely TNL-based).
// Offsets:
// +0x54: mChunkState (non-zero indicates a chunk is pending)
// +0x1c: mBufferBase (start of internal buffer)
// +0x08: mWritePos (current write pointer)
// +0x18: mBufferEnd (end of buffer)
void PacketBuffer::processChunkType6() {
    if (mChunkState != 0) {
        int* chunkData = (int*)(mBufferBase + mChunkState);
        if (*chunkData != 6) {
            flushBuffer(); // FUN_00635a80
            return;
        }
        // Copy the two ints from the current write position - 2 to the current position
        int* writePtr = mWritePos;
        writePtr[0] = writePtr[-2];
        writePtr[1] = writePtr[-1];
        // Insert the chunk header (type 6 and the second int from chunk) at the position before the write pointer
        mWritePos[-2] = *chunkData;   // Always 6
        mWritePos[-1] = chunkData[1]; // Second int from chunk
        // Check if there is enough space for the upcoming 8 bytes (2 ints)
        if (mBufferEnd - mWritePos < 9) {
            expandBuffer(); // FUN_00635c70
        }
        // Advance write position by 8 bytes (2 ints)
        mWritePos += 8;
        processInternal(); // FUN_006362d0
    }
    flushBuffer(); // FUN_00635a80
}