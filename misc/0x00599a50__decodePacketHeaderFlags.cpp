// FUNC_NAME: decodePacketHeaderFlags
// Address: 0x00599a50
// Role: Extracts a 24-bit field from bits 8-31 of a 32-bit word and conditionally sets the low byte
//       to 1 if bit 0 is set and bit 4 is clear. Likely used to decode a network packet header
//       (sequence number + ack/piggyback flag) from the EARS engine.
int __fastcall decodePacketHeaderFlags(uint32_t* headerWord)
{
    uint32_t word = *headerWord;
    // Extract bits 8-31 (upper 24 bits) - typically used as sequence number.
    uint32_t sequence24 = (word >> 8) & 0xFFFFFF;
    // Condition: bit 4 (0x10) is clear AND bit 0 (0x01) is set.
    // If true, the low byte of the result is set to 1 (indicating ack/flag), else 0.
    if (((word & 0x10) == 0) && ((word & 0x01) != 0))
    {
        return (int)((sequence24 << 8) | 0x01);
    }
    return (int)(sequence24 << 8);
}