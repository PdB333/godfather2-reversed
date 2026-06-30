// FUNC_NAME: TNL::PacketHeader::init

// Initializes a TNL packet header with a given sequence number and ack mask.
// The ack mask (128-bit) is copied from the connection's receive window.
// Structure size: 0x30 (48 bytes)
//   +0x00: m_flags (uint32) - packet flags, set to 1
//   +0x04: field_04 (uint16) - unknown, zeroed
//   +0x06: field_06 (uint16) - unknown, zeroed
//   +0x08: field_08 (uint32)
//   +0x0C: field_0C (uint32)
//   +0x10: field_10 (uint32)
//   +0x14: field_14 (uint32)
//   +0x18: m_sequence (uint32) - packet sequence number
//   +0x1C: m_ackMask[4] (uint32) - 128-bit acknowledgment bitmask
//   +0x2C: field_44 (uint32) - usually zeroed

void __thiscall PacketHeader::init(const uint32_t* ackMaskSource, uint32_t sequence)
{
    m_sequence = sequence;                         // +0x18
    m_flags = 1;                                   // +0x00
    field_04 = 0;                                  // +0x04
    field_06 = 0;                                  // +0x06
    field_08 = 0;                                  // +0x08
    field_0C = 0;                                  // +0x0C
    field_10 = 0;                                  // +0x10
    field_14 = 0;                                  // +0x14
    m_ackMask[0] = ackMaskSource[0];               // +0x1C
    m_ackMask[1] = ackMaskSource[1];               // +0x20
    m_ackMask[2] = ackMaskSource[2];               // +0x24
    m_ackMask[3] = ackMaskSource[3];               // +0x28
    field_44 = 0;                                  // +0x2C
}