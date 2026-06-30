// FUNC_NAME: PacketWriter::writeTripleData
// Address: 0x00633ac0
// Role: Writes three 8-byte data blocks into the serialization buffer,
//       then processes the written block (e.g., encodes/checksums it),
//       and finally adjusts the buffer position by trimming 8 bytes
//       (likely for a header or alignment purpose).

class PacketWriter
{
public:
    // Assumed member variable offsets:
    // +0x00: unknown (maybe vtable pointer)
    // +0x04: unknown
    // +0x08: mCurrentPos (pointer to current write position in buffer)
    // +0x0C: unknown
    // +0x10: unknown
    // +0x14: unknown
    // +0x18: mBufferEnd (pointer to end of allocated buffer)
    // +0x1C: unknown or possibly buffer capacity

    void writeTripleData(const uint32_t* data1, const uint32_t* data2, const uint32_t* data3);
};

// Forward declarations of helpers (not part of this function)
void growBuffer(); // 0x00635c70 - grows the internal buffer
void encodeBlock(PacketWriter* self, int startOffset, int flag); // 0x006362d0 - processes a range of written data

void PacketWriter::writeTripleData(const uint32_t* data1, const uint32_t* data2, const uint32_t* data3)
{
    uint32_t* currentPos = *reinterpret_cast<uint32_t**>(reinterpret_cast<uint32_t>(this) + 0x8);

    // Write first 8 bytes (two 32-bit values) from data1
    currentPos[0] = data1[0];
    currentPos[1] = data1[1];

    // Write second 8 bytes from data2 at offset 8
    uint32_t* posAfterFirst = currentPos; // pointer arithmetic
    posAfterFirst[2] = data2[0];
    posAfterFirst[3] = data2[1];

    // Write third 8 bytes from data3 at offset 0x10 (16)
    uint32_t* posAfterSecond = currentPos;
    posAfterSecond[4] = data3[0];
    posAfterSecond[5] = data3[1];

    // Check if there's enough space left in the buffer for the written 24 bytes (0x18)
    int currentOffset = reinterpret_cast<int>(currentPos);
    int bufferEnd = *reinterpret_cast<int*>(reinterpret_cast<uint32_t>(this) + 0x18);
    if (bufferEnd - currentOffset < 0x19) // If less than 25 bytes remain
    {
        growBuffer(); // Possibly grow the buffer or handle overflow
    }

    // Advance the current position by 24 bytes (total written)
    *reinterpret_cast<int*>(reinterpret_cast<uint32_t>(this) + 0x8) = currentOffset + 0x18;

    // Call helper to process/encode the just-written block (starting at old currentPos, flag=1)
    encodeBlock(this, currentOffset, 1);

    // Move the buffer pointer back by 8 bytes (0x10 net forward from original)
    // This effectively discards the last 8 bytes of the written data,
    // perhaps because they were used as scratch or for a checksum that is now stored elsewhere.
    *reinterpret_cast<int*>(reinterpret_cast<uint32_t>(this) + 0x8) -= 8;

    return;
}