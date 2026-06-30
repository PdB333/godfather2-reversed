// FUNC_NAME: StreamReader::readPackedBlock
// Function address: 0x0048dda0
// Reads a packed data block from the internal read pointer (offset 0x18)
// and invokes a callback with the block header (64-bit split into two 32-bit values).
// Block format: [8-byte header][64-byte payload][4-byte size][4-byte alignment padding]
void __thiscall StreamReader::readPackedBlock(void* thisPtr, void (*callback)(uint32_t, uint32_t))
{
    // Read pointer stored at offset 0x18
    uint8_t* readPtr = *(uint8_t**)((uintptr_t)thisPtr + 0x18);

    // Align to 4-byte boundary (round up)
    uint8_t* blockStart = (uint8_t*)(((uintptr_t)readPtr + 3) & ~3);

    // Read 8-byte header (e.g. type/identifier)
    uint64_t header = *(uint64_t*)blockStart;

    // Advance read pointer past the header
    *(uint8_t**)((uintptr_t)thisPtr + 0x18) = blockStart + 8;

    // Copy 64 bytes of payload to local buffer (may be used externally via stack frame)
    uint8_t payload[64];
    memcpy(payload, blockStart + 8, 0x40);

    // Advance read pointer past the payload
    *(uint8_t**)((uintptr_t)thisPtr + 0x18) = blockStart + 72; // 8 + 64

    // Read next two integers: size and alignment factor (power of 2)
    uint32_t size = *(uint32_t*)(blockStart + 72);
    uint32_t alignment = *(uint32_t*)(blockStart + 76);

    // Advance read pointer past these two integers
    *(uint8_t**)((uintptr_t)thisPtr + 0x18) = blockStart + 80; // 72 + 8

    // Compute new read pointer: align size to 4, then align (blockStart + alignment + 0x4f) to alignment boundary
    uint32_t alignedSize = (size + 3) & ~3;
    uint32_t alignedEnd = ((uintptr_t)blockStart + alignment + 0x4f) & ~(alignment - 1);
    *(uint32_t*)((uintptr_t)thisPtr + 0x18) = alignedSize + alignedEnd;

    // Copy payload to another local buffer (appears unused – likely for stack-based callback access)
    uint32_t payloadCopy[16]; // 64 bytes
    memcpy(payloadCopy, payload, 0x40);

    // Split header and call callback
    uint32_t headerLow  = (uint32_t)header;
    uint32_t headerHigh = (uint32_t)(header >> 32);
    callback(headerLow, headerHigh);
}