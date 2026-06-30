// FUNC_NAME: StreamReader::readPackedData()
void __thiscall StreamReader::readPackedData(StreamReader *this, void (*callback)(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
{
    uint32_t header;
    uint32_t lo1, hi1, lo2, hi2;
    uint64_t val1, val2;
    uint8_t *alignedPos;

    // Current read pointer stored at +0x18
    uint8_t *curPos = this->readPos;

    // Read 32-bit header from current position
    header = *(uint32_t *)curPos;

    // Align the pointer to the next 4-byte boundary (round up)
    alignedPos = (uint8_t *)(((uint32_t)curPos + 7) & 0xFFFFFFFC);

    // Read two 64-bit values (e.g., doubles or packed data)
    val1 = *(uint64_t *)alignedPos;
    val2 = *(uint64_t *)(alignedPos + 8);

    // Advance the stream position past the 16 bytes read
    this->readPos = alignedPos + 16;

    // Split into high/low 32-bit halves (little-endian)
    lo1 = (uint32_t)val1;
    hi1 = (uint32_t)(val1 >> 32);
    lo2 = (uint32_t)val2;
    hi2 = (uint32_t)(val2 >> 32);

    // Invoke the callback with header and the two 64-bit values as 32-bit halves
    callback(header, lo1, hi1, lo2, hi2);
}