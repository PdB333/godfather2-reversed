// FUNC_NAME: PacketHeader::initWithAck
// Address: 0x005ac020
// Role: Initializes a packet header structure, setting flags and storing an ACK/sequence value.
void __fastcall PacketHeader_initWithAck(uint32_t* header, uint32_t ackValue)
{
    // Bitmask: keep bits 31-16, bit15, bit3; then force bit3 to 1
    *header = (*header & 0xFFFF8008) | 0x8;
    // Clear upper 16 bits of the first dword (bytes 2-3) – likely resetting flags or sequence upper half
    *(uint16_t*)((uint8_t*)header + 2) = 0;
    // Set bit 15 to indicate the packet contains an acknowledgment field
    *header |= 0x8000;
    // Write the second dword (offset +4) with the provided ACK/sequence value
    header[1] = ackValue;
}