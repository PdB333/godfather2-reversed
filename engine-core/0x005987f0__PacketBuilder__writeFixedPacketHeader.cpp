// FUNC_NAME: PacketBuilder::writeFixedPacketHeader
// Address: 0x005987f0
// Creates a small packet: writes a 2-byte value (0x0002) and a 4-byte value (0x00000802) into an internal buffer.
// Returns total packet size as constant 8 (likely includes 2-byte length field written by first vtable call).
// The global DAT_01205590 points to a singleton with a vtable entry at offset 0x10 used for writing data.

__thiscall int PacketBuilder::writeFixedPacketHeader(void)
{
    uint32_t data32 = 0x802;                // +0x08: 4-byte payload data
    uint16_t data16 = 2;                    // +0x10: 2-byte sub‑type  
    uint32_t *ptrData32 = &data32;          // +0x14: pointer to 4‑byte payload

    // First call probably writes a 2‑byte length field (e.g. total size 8)
    (*(void (**)(void))(*DAT_01205590 + 0x10))();

    // Write 2‑byte value (data16) at offset this+2
    (*(void (**)(int, uint16_t*, int))(*DAT_01205590 + 0x10))(this + 2, &data16, 2);

    // Write 4‑byte value (0x802) via pointer at offset this+4
    (*(void (**)(int, uint32_t**, int))(*DAT_01205590 + 0x10))(this + 4, &ptrData32, 4);

    return 8;   // predefined packet size (2+2+4 = 8 bytes)
}