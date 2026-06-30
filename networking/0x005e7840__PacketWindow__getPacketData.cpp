// FUNC_NAME: PacketWindow::getPacketData
// Function at 0x005E7840: Retrieves packet data given an encoded packet ID.
// The packet ID is a 32-bit value that must be in the range [0xAD103100, 0xAD1031FF].
// The low byte is used as an index into an array of packet record pointers.
// Validates that the index is less than the packet count and that the pointer exists.
// Then copies a 16-byte structure from offset 0x40 of the record to the output.

#define PACKET_MAGIC 0xAD103100

bool PacketWindow::getPacketData(uint packetId, PacketData* outData)
{
    // packet count stored as byte at this+0x1C
    byte packetCount = *(byte*)(this + 0x1C);

    // Default return: failure
    bool result = false;

    // Validate: after XOR with magic, the result must be < packetCount.
    // Also the low byte of packetId (which is unchanged by XOR) must be < packetCount.
    if ((packetId ^ PACKET_MAGIC) < (uint)packetCount && packetCount != 0 && (byte)packetId < packetCount)
    {
        // Index into array of pointers at this+4 (each pointer 4 bytes)
        int recordPtr = *(int*)(this + 4 + (packetId & 0xFF) * 4);

        if (recordPtr != 0)
        {
            // Copy 16 bytes from offset 0x40 of the packet record to output
            outData->field0 = *(uint*)(recordPtr + 0x40);
            outData->field4 = *(uint*)(recordPtr + 0x44);
            outData->field8 = *(uint*)(recordPtr + 0x48);
            outData->fieldC = *(uint*)(recordPtr + 0x4C);
            result = true;
        }
    }

    return result;
}