// FUNC_NAME: PacketUtils::buildPacketHeader
// Address: 0x0056ae80
// Constructs a 32-bit packet header from a sequence number (in EAX) and a 16-bit payload.
// The resulting header is combined as:
//   bits 31-22: (16-bit field from (seq+0x10000) masked to 10 bits, shifted left 14)
//   bits 21-16: lower 6 bits of sequence number
//   bits 15-0 : payload
// The combined header is then passed to a lower-level send routine (0x0056aab0).

void PacketUtils::buildPacketHeader(uint32_t unusedParam, uint16_t payload)
{
    // local_4 holds the constructed header
    uint32_t header;

    // in_EAX is assumed to be a global sequence number (or register variable)
    // We model it as a compiler-intrinsic; in practice it would come from a connection state.
    uint32_t sequence = in_EAX;   // typically passed in EAX register

    // Build the header by packing various fields
    header = ((sequence + 0x10000) & 0x3ff00) << 0xe          // bits 31-22
           | (sequence & 0x3f) << 0x10                         // bits 21-16
           | payload;                                          // bits 15-0

    // Buffer for packet data (likely a stack-allocated temporary)
    uint8_t packetBuffer[4];   // uninitialized in original, but probably filled by send function

    // Send or queue the packet
    // FUN_0056aab0 likely expects a pointer to a packet buffer and the header?
    FUN_0056aab0(packetBuffer);  // callee address 0x0056aab0

    return;
}