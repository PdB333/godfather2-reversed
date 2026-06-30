// FUNC_NAME: StreamReader::readChunk

void StreamReader::readChunk(ChunkHandler* handler)
{
    // param_1 is 'this'
    // +0x18: current position pointer in the stream buffer
    uint32_t* basePtr = *(uint32_t**)(this + 0x18);
    // Align to 4 bytes
    basePtr = (uint32_t*)(((uint32_t)basePtr + 3) & ~3);
    *(uint32_t**)(this + 0x18) = basePtr;

    // Read 8-byte header (likely a type/ID or size)
    uint64_t header = *(uint64_t*)basePtr;
    *(uint32_t**)(this + 0x18) = basePtr + 2; // advance by 2 uint32_t (8 bytes)

    // Copy 32-byte data block into local buffer
    char dataBlock[32];
    __memcpy(dataBlock, basePtr + 2, 32);
    *(uint32_t**)(this + 0x18) = basePtr + 10; // basePtr + 2 for header + 8 for data = +10 uint32_t

    // Read two size fields after the data block
    int32_t elementCount = *(int32_t*)(basePtr + 10);      // at +0x28 in uint32_t offset
    int32_t elementSize  = *(int32_t*)(basePtr + 11);      // at +0x2c
    *(uint32_t**)(this + 0x18) = basePtr + 12;             // advance over these two ints

    // Calculate end of array area: align to elementSize boundary
    uint32_t arrayOffset = ((uint32_t)(basePtr + 12) + elementSize - 1) & ~(elementSize - 1);
    uint32_t alignedSize = (elementCount + 3) & ~3;        // align elementCount to 4 bytes
    *(uint32_t*)(this + 0x18) = alignedSize + arrayOffset;

    // Build the arguments for the callback
    uint32_t arg6 = (elementCount != 0) ? 0 : arrayOffset; // equivalent to -(uint)(iVar2 != 0) & uVar5
    uint32_t arg7 = elementCount;
    uint32_t arg8 = 1;

    // Call the handler function with parsed data
    handler->funcPtr(header, dataBlock, arg6, arg7, arg8);
}