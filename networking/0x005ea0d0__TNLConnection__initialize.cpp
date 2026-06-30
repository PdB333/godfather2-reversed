// FUNC_NAME: TNLConnection::initialize
void TNLConnection::initialize(void)
{
    // +0x80: 8-byte sequence number or timestamp (set to 0)
    *(uint64 *)(this + 0x80) = 0;
    // +0x168: some 4-byte field (set to 0)
    *(uint32 *)(this + 0x168) = 0;
    // +0x00: first byte of object (likely vtable or type flag) set to 0
    *(uint8 *)this = 0;
    // +0x130: 4-byte field (set to 0)
    *(uint32 *)(this + 0x130) = 0;
    // +0xf8: 4-byte field (set to 0)
    *(uint32 *)(this + 0xf8) = 0;
    // +0x9c: invalid ID or sentinel (-1)
    *(int32 *)(this + 0x9c) = -1;
    // +0xa0: another invalid ID (-1)
    *(int32 *)(this + 0xa0) = -1;
    // +0xfd, +0xfe, +0xff: three bytes (flags or state) set to 0
    *(uint8 *)(this + 0xfd) = 0;
    *(uint8 *)(this + 0xfe) = 0;
    *(uint8 *)(this + 0xff) = 0;
    // +0x100: 4-byte field (set to 0)
    *(uint32 *)(this + 0x100) = 0;
    // +0x108: 4-byte field (set to 0)
    *(uint32 *)(this + 0x108) = 0;
    // +0xfc: connection state (set to 3 = Connected)
    *(uint8 *)(this + 0xfc) = 3;
    // +0x104: packet window size (set to 32 slots)
    *(uint32 *)(this + 0x104) = 0x20;
    // +0x10c, +0x114: two 8-byte fields (set to 0)
    *(uint64 *)(this + 0x10c) = 0;
    *(uint64 *)(this + 0x114) = 0;
    // +0x134: pointer to some global (e.g., connection manager)
    *(uint32 *)(this + 0x134) = DAT_00e2eff4;
    // +0xa4: 4-byte field (set to 0)
    *(uint32 *)(this + 0xa4) = 0;
    // +0x94: pointer to another global (e.g., network manager)
    *(uint32 *)(this + 0x94) = DAT_00e4459c;
    // +0x88: receive buffer size (0x1000 = 4096 bytes)
    *(uint32 *)(this + 0x88) = 0x1000;
    // +0x8c: send buffer size (0x1000 = 4096 bytes)
    *(uint32 *)(this + 0x8c) = 0x1000;
    // +0x90: some offset or counter (set to 0)
    *(uint32 *)(this + 0x90) = 0;
    // +0x98: another field (set to 0)
    *(uint32 *)(this + 0x98) = 0;
    return;
}