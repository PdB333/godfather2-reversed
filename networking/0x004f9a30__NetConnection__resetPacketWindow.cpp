// FUNC_NAME: NetConnection::resetPacketWindow
void __thiscall NetConnection::resetPacketWindow() {
    // +0x0: mCurrentSequence number (starting packet sequence)
    *(uint32_t*)(this + 0x0) = 0;
    // +0x4: mWindowSize (default packet window size = 10)
    *(uint32_t*)(this + 0x4) = 10;
    // +0x8 to +0x58: mPacketState[21] (array of packet status bits/ids)
    *(uint32_t*)(this + 0x8) = 0;
    *(uint32_t*)(this + 0xC) = 0;
    *(uint32_t*)(this + 0x10) = 0;
    *(uint32_t*)(this + 0x14) = 0;
    *(uint32_t*)(this + 0x18) = 0;
    *(uint32_t*)(this + 0x1C) = 0;
    *(uint32_t*)(this + 0x20) = 0;
    *(uint32_t*)(this + 0x24) = 0;
    *(uint32_t*)(this + 0x28) = 0;
    *(uint32_t*)(this + 0x2C) = 0;
    *(uint32_t*)(this + 0x30) = 0;
    *(uint32_t*)(this + 0x34) = 0;
    *(uint32_t*)(this + 0x38) = 0;
    *(uint32_t*)(this + 0x3C) = 0;
    *(uint32_t*)(this + 0x40) = 0;
    *(uint32_t*)(this + 0x44) = 0;
    *(uint32_t*)(this + 0x48) = 0;
    *(uint32_t*)(this + 0x4C) = 0;
    *(uint32_t*)(this + 0x50) = 0;
    *(uint32_t*)(this + 0x54) = 0;
    *(uint32_t*)(this + 0x58) = 0;
    // +0xAC: mAckBitsLow (acknowledge bitmask lower)
    *(uint32_t*)(this + 0xAC) = 0;
    // +0xB0: mAckBitsHigh (acknowledge bitmask upper)
    *(uint32_t*)(this + 0xB0) = 0;
}