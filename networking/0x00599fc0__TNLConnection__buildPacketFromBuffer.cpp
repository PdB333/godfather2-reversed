// FUNC_NAME: TNLConnection::buildPacketFromBuffer

// Address: 0x00599fc0
// Role: Constructs a network packet from a raw buffer, validating sizes and setting header fields.
//       Reads a combined stream identifier from four header bytes, then allocates a packet via FUN_00599aa0.
//       If payload count > 0, writes payload metadata into the packet structure.

void __fastcall TNLConnection::buildPacketFromBuffer(void* thisPtr)
{
    // +0x8: pointer to a buffer containing raw packet data (PacketBuffer)
    PacketBuffer* pBuffer = *(PacketBuffer**)((char*)thisPtr + 8);

    // Validate buffer: the ushort at +2 (flags?) must equal the computed total header size
    // Total size = (numPayloads at +0x14) * 16 + 24 (24-byte header + 16-byte payloads)
    if ((uint16)pBuffer->flags != (pBuffer->numPayloads * 16u + 24))
    {
        // Crash/assert handler (indirect call via global function pointer)
        (**(code**)(*DAT_01205590 + 4))();
    }

    // Build 32-bit stream ID from four bytes at offsets +4, +8, +0xC, +0x10 (big‑endian)
    // Each is stored as an int but only the lowest byte is used; we combine via shifts
    uint32 streamId = (uint8)(pBuffer->field_4) << 24 |
                      (uint8)(pBuffer->field_8) << 16 |
                      (uint8)(pBuffer->field_C) << 8  |
                      (uint8)(pBuffer->field_10);

    // Allocate a new packet for this stream (returns pointer to packet structure)
    Packet* pPacket = FUN_00599aa0(thisPtr, streamId);
    if (pPacket == nullptr)
    {
        // Allocation failure – abort
        (**(code**)(*DAT_01205590 + 4))();
        return;
    }

    int payloadCount = pBuffer->numPayloads;  // +0x14: number of payload items
    if ((ushort)payloadCount > 0xFFFF)
    {
        // Overflow protection
        (**(code**)(*DAT_01205590 + 4))();
    }

    short cnt = (short)payloadCount;
    if (cnt != 0)
    {
        // Write payload header into the packet
        pPacket->field_18 = 0;                // +0x18: 4 bytes, reserved/zeroed
        pPacket->field_1c = 1;                // +0x1c: 2 bytes, type/flag?
        pPacket->numPayloads = cnt;           // +0x1e: 2 bytes, number of payloads
        pPacket->payloadData = (char*)pBuffer + 0x18;  // +0x24: pointer to first payload
        pPacket->someFlag = 1;               // +0x20: 2 bytes, flag (e.g. "has payloads")
    }

    // Clear low two bits of packet flags (alignment/reserved)
    pPacket->flags &= 0xFFFFFFFCu;           // +0x10: 4 bytes, flags
}