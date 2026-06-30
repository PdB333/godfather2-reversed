// FUN_NAME: GhostPacket::GhostPacket
void __thiscall GhostPacket::GhostPacket(void) {
    // +0x00: likely packet header field (maybe flags or sequence base)
    *(int *)(this + 0x00) = 0;
    // +0x04: packet type identifier (10 = GhostPacket)
    *(int *)(this + 0x04) = 10;
    // Zero out 21 consecutive 4-byte fields from +0x08 to +0x58
    *(int *)(this + 0x08) = 0;
    *(int *)(this + 0x0C) = 0;
    *(int *)(this + 0x10) = 0;
    *(int *)(this + 0x14) = 0;
    *(int *)(this + 0x18) = 0;
    *(int *)(this + 0x1C) = 0;
    *(int *)(this + 0x20) = 0;
    *(int *)(this + 0x24) = 0;
    *(int *)(this + 0x28) = 0;
    *(int *)(this + 0x2C) = 0;
    *(int *)(this + 0x30) = 0;
    *(int *)(this + 0x34) = 0;
    *(int *)(this + 0x38) = 0;
    *(int *)(this + 0x3C) = 0;
    *(int *)(this + 0x40) = 0;
    *(int *)(this + 0x44) = 0;
    *(int *)(this + 0x48) = 0;
    *(int *)(this + 0x4C) = 0;
    *(int *)(this + 0x50) = 0;
    *(int *)(this + 0x54) = 0;
    *(int *)(this + 0x58) = 0;
    // Additional fields at the end of the packet
    *(int *)(this + 0xAC) = 0;
    *(int *)(this + 0xB0) = 0;
    return;
}