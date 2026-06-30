// FUNC_NAME: TNLConnection::buildReliablePacket
// Function address: 0x00653230
// Role: Builds a reliable packet for TNL networking, serializing sequence number, ack bits, and data into a bitstream.
// Uses 32-slot packet window offsets: +0x90 (unacknowledged packet data), +0x98 (current sequence/index), +0xa0 (last ack'd sequence),
// +0x9c (data buffer start), +0xc (base offset), +0x1a4 (pointer to connection state with +100 offset for max bits).

void TNLConnection::buildReliablePacket(void* thisPtr, uint32_t* notifyList)
{
    byte* pbVar1;
    void* (*debugBreak)();
    int bitStream;
    char bVar4;
    int local_c;
    uint32_t* local_8;
    uint32_t local_4;

    // Check if debug mode requires breakpoint
    bVar4 = someDebugCheck(); // FUN_00653da0
    if ((bVar4 != '\0') && (notifyList == (uint32_t*)0x0)) {
        debugBreak = (void* (*)())swi(3);
        (*debugBreak)();
        return;
    }

    // Calculate number of bytes needed for the packet data (difference between current and ack'd positions, rounded up to byte)
    uint32_t dataSizeBits = *(uint32_t*)(thisPtr + 0x90) - *(uint32_t*)(thisPtr + 0xa0);
    uint32_t dataSizeBytes = (dataSizeBits + 7) >> 3; // (size in bits + 7) / 8

    if (notifyList == (uint32_t*)0x0) {
        // Increment sequence number when not externally supplied
        *(uint32_t*)(thisPtr + 0x98) = *(uint32_t*)(thisPtr + 0x98) + 1;
    }

    // Serialize packet control fields to bitstream
    local_8 = notifyList;
    writeBitfield(2, &local_8); // write packet type (reliable)
    local_8 = *(uint32_t**)(thisPtr + 0x98); // sequence number
    writeBitfield(5, &local_8); // write sequence (5 bits? or size=5)
    // Check if bitstream buffer is full, expand if needed
    // in_EAX is actually a global bitstream pointer (likely from a register)
    bitStream = getBitStream(); // retrieved from some register, e.g., in_EAX
    if (*(uint32_t*)(bitStream + 0x30) < *(uint32_t*)(bitStream + 0x18) + 1) {
        bVar4 = bitStreamExpand(); // FUN_0064b7c0
        if (bVar4 == '\0') goto skipAckBits;
    }
    // Write ack bits (bitmask) for the 32-slot window
    pbVar1 = (byte*)((*(uint32_t*)(bitStream + 0x18) >> 3) + *(uint32_t*)(bitStream + 0xc));
    *pbVar1 = *pbVar1 | '\x01' << ((byte)(*(uint32_t*)(bitStream + 0x18)) & 7);
    *(uint32_t*)(bitStream + 0x18) = *(uint32_t*)(bitStream + 0x18) + 1;
skipAckBits:
    // Write ack mask (shifted 5 bits)
    local_8 = (uint32_t*)(*(uint32_t*)(thisPtr + 0x98) >> 5);
    writeBitfield(6, &local_8); // write ack mask (6 bits?)
    local_8 = *(uint32_t**)(thisPtr + 0x90); // unacked packet data pointer
    writeBitfield(10, &local_8); // write some flag (10 bits?)
    local_8 = (uint32_t*)0x0;
    writeBitfield(0, &local_8); // write zero (align?)
    // Write data size in bytes (using an opcode derived from global constant)
    local_8 = (uint32_t*)dataSizeBytes;
    uint8_t opcode = (uint8_t)(DAT_00e2dd14 >> 0x17) + (uint8_t)-0x7e; // likely 0x82 (130)
    writeBitfield(opcode, &local_8); // write size

    // Write actual data in 4-byte chunks
    uint32_t numChunks = dataSizeBytes >> 2; // number of 32-bit words (rounded up)
    uint32_t i = 0;
    uint32_t* dataPtr = (uint32_t*)(thisPtr + 0x9c); // data buffer
    uint32_t bitsThisChunk;
    for (i = 0; i < numChunks; i++) {
        if (i == numChunks - 1) {
            bitsThisChunk = (dataSizeBytes - (i * 4)) * 8; // remaining bits in last chunk
        } else {
            bitsThisChunk = 0x20; // 32 bits
        }
        local_4 = *dataPtr;
        writeBitfield(bitsThisChunk & 0xff, &local_4);
        dataPtr++;
    }

    // Compute and write max allowed bits for this packet (clamped to 2047)
    int maxBits = *(uint32_t*)(*(uint32_t*)(thisPtr + 0x1a4) + 100) - *(uint32_t*)(thisPtr + 0xc);
    if (maxBits > 0x7ff) maxBits = 0x7ff; // 2047
    maxBits >>= 3; // convert to bytes
    writeBitfield(8, &maxBits); // write byte count (8 bits)

    // If not externally notified, store the packet data pointer in the send window
    if (notifyList == (uint32_t*)0x0) {
        uint32_t slotIndex = *(uint32_t*)(thisPtr + 0x98) & 0x1f; // 32-slot window
        *(uint32_t*)(thisPtr + 0x10 + slotIndex * 4) = *(uint32_t*)(thisPtr + 0x90); // save pointer
    }
    return;
}