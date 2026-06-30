// FUNC_NAME: NetBuffer::writeAlignedBlock
// Address: 0x00461a30
// Writes a header (type, count, alignment) then copies an aligned data block of `count * 0x40` bytes.
// The write pointer is at offset +0x14 in the class.
void NetBuffer::writeAlignedBlock(uint32_t type, void* data, int count, int alignment)
{
    // Write 12-byte header: type, count, alignment
    *(uint32_t*)(this->writePtr) = type;
    this->writePtr += 4;
    *(int*)(this->writePtr) = count;
    this->writePtr += 4;
    *(int*)(this->writePtr) = alignment;
    this->writePtr += 4;

    // Align write pointer to the next multiple of `alignment`
    uint32_t alignMask = alignment - 1;
    uint8_t* aligned = (uint8_t*)((uintptr_t)(this->writePtr + alignMask) & ~alignMask);
    this->writePtr = aligned;

    // Copy the data (each element is 64 bytes)
    size_t dataSize = count * 0x40;
    memcpy(this->writePtr, data, dataSize);
    this->writePtr += dataSize;
}