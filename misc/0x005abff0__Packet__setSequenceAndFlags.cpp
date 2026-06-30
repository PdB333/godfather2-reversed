// FUNC_NAME: Packet::setSequenceAndFlags
void __fastcall Packet::setSequenceAndFlags(uint sequence) {
    // Set flags: bit 2 (0x4) and bit 15 (0x8000), clear others
    // This is a specific packet initialization pattern
    m_flags = (m_flags & 0xffff8004) | 4;   // +0x00: keep upper 16 bits, clear lower except bit2, then ensure bit2 set
    *(uint16*)((byte*)this + 2) = 0;        // +0x02: clear upper 16 bits of flags (set to 0)
    m_flags |= 0x8000;                      // +0x00: set bit15 (likely "reliable" or "valid")
    m_sequence = sequence;                  // +0x04: store sequence number
}