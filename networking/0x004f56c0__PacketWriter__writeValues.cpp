// FUNC_NAME: PacketWriter::writeValues
// Function at 0x004f56c0: Writes multiple values into a buffer aligned to 4-byte boundaries.
// Used for serializing packet fields (typically from TNL networking layer).
// The 'this' pointer contains a current write cursor at offset +0x14.
// Values are written in order: val1, val2, val3, val8 (64-bit), val4, and an extra value passed in ESI.

void PacketWriter::writeValues(uint32_t val1, uint32_t val2, uint32_t val3, uint64_t val8,
                              uint32_t val4, uint32_t val5) // val5 comes from ESI (register)
{
    uint32_t* cursor = *(uint32_t**)((uint8_t*)this + 0x14); // +0x14: current write pointer

    // Write val1 with alignment
    *cursor = val1;
    cursor = (uint32_t*)(((uint32_t)cursor + 7) & 0xFFFFFFFC); // align to next 4-byte boundary
    *(uint32_t**)((uint8_t*)this + 0x14) = cursor;

    // Write val2 with alignment
    *cursor = val2;
    cursor = (uint32_t*)(((uint32_t)cursor + 7) & 0xFFFFFFFC);
    *(uint32_t**)((uint8_t*)this + 0x14) = cursor;

    // Write val3 with alignment
    *cursor = val3;
    cursor = (uint32_t*)(((uint32_t)cursor + 7) & 0xFFFFFFFC);
    *(uint32_t**)((uint8_t*)this + 0x14) = cursor;

    // Write 8-byte val8 with alignment, then advance by 8 bytes
    uint64_t* cursor8 = (uint64_t*)(((uint32_t)cursor + 7) & 0xFFFFFFFC);
    *(uint64_t**)((uint8_t*)this + 0x14) = cursor8;
    *cursor8 = val8;
    // Advance by 8 (no alignment needed after 8-byte write)
    *(uint32_t*)((uint8_t*)this + 0x14) = (uint32_t)cursor8 + 8;

    // Write val4 (4 bytes)
    uint32_t* next = *(uint32_t**)((uint8_t*)this + 0x14);
    *next = val4;
    *(uint32_t*)((uint8_t*)this + 0x14) = (uint32_t)next + 4;

    // Write val5 (from ESI, passed as extra parameter)
    next = *(uint32_t**)((uint8_t*)this + 0x14);
    *next = val5;
    *(uint32_t*)((uint8_t*)this + 0x14) = (uint32_t)next + 4;
}