// FUNC_NAME: NetSession::encodePacketID
// Address: 0x0056ae80
// Encodes a 32-bit packet identifier from a sequence base (member) and extra data (ushort).
// The packed value is stored in a 4-byte buffer and then processed by FUN_0056aab0.
// Bit layout: bits 31:22 from (m_sequenceBase+0x10000) & 0x3FF00, bits 21:16 from m_sequenceBase & 0x3f, bits 15:0 from extraData.

void __thiscall NetSession::encodePacketID(ushort extraData)
{
    uint base = m_sequenceBase; // member variable (likely +0x? offset)
    uint packed = ((base + 0x10000) & 0x3FF00) << 14 | (base & 0x3F) << 16 | extraData;
    char buffer[4];
    *(uint*)buffer = packed;
    FUN_0056aab0(buffer); // process the encoded buffer
}