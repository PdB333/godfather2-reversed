// FUNC_NAME: BufferWriter::writeAlignedBlock
// Address: 0x0048e330
// This function writes a fixed-size 32-byte header, followed by a data size and alignment field,
// then copies a variable-length data buffer aligned to the specified alignment.
// The write pointer is stored at offset +0x14 from 'this'.

void BufferWriter::writeAlignedBlock(const void* header32Bytes, const void* data, size_t dataSize, int alignment)
{
    // Current write pointer from object (offset +0x14)
    char* writePtr = *(char**)(this + 0x14);
    
    // Align current pointer to 4-byte boundary (for header copy)
    writePtr = (char*)((uintptr_t)(writePtr + 3) & ~3U);
    *(char**)(this + 0x14) = writePtr;
    
    // Copy the 32-byte header
    memcpy(writePtr, header32Bytes, 0x20);
    writePtr += 0x20;
    *(char**)(this + 0x14) = writePtr;
    
    // Store the data size (size_t, 4 bytes)
    *(size_t*)writePtr = dataSize;
    writePtr += 4;
    *(char**)(this + 0x14) = writePtr;
    
    // Store the alignment value (int, 4 bytes)
    *(int*)writePtr = alignment;
    // Note: writePtr still points to the alignment field; we do NOT increment yet.
    
    // Align the next write position according to the stored alignment value.
    // This ensures the data begins at a multiple of 'alignment'.
    char* alignedDataPtr = (char*)(~(alignment - 1U) & (uintptr_t)(alignment + 3 + writePtr));
    *(char**)(this + 0x14) = alignedDataPtr;
    
    // Copy the data block
    memcpy(alignedDataPtr, data, dataSize);
    
    // Advance write pointer by the aligned data size (round up to next 4)
    size_t alignedDataSize = (dataSize + 3U) & ~3U;
    *(char**)(this + 0x14) = alignedDataPtr + alignedDataSize;
}