// FUNC_NAME: Packet::initialize(uint type)
void __thiscall Packet::initialize(uint type) {
    // Increment global packet counter
    g_packetCounter++; // _DAT_01205a30

    // Zero out flags/short fields
    // Offset 0x00: short unknownFlag1
    *(undefined2 *)this = 0;
    // Offset 0x02: short unknownFlag2
    *(undefined2 *)((uint)this + 2) = 0;
    // Offset 0x04: int packetType (from parameter)
    *(uint *)((uint)this + 4) = type;
    // Zero out three int fields (offsets 0x08, 0x0C, 0x10)
    *(uint *)((uint)this + 8) = 0;
    *(uint *)((uint)this + 12) = 0;
    *(uint *)((uint)this + 16) = 0;

    // htonl(0) call – likely a macro expansion, result unused
    htonl(0);
}