// FUNC_NAME: TNLConnection::resetPacketSlot
void __fastcall TNLConnection::resetPacketSlot(void* thisPtr)
{
    // Zero out the packet slot structure (size ~0x98 bytes)
    // Offsets are based on analysis of the decompiled output

    uint64_t* p64 = (uint64_t*)thisPtr;
    p64[0] = 0;                 // +0x00 : first 8-byte field
    p64[1] = 0;                 // +0x08 : second 8-byte field

    uint32_t* p32 = (uint32_t*)thisPtr;
    p32[4] = 0;                 // +0x10
    p32[5] = 0;                 // +0x14
    p32[6] = 0;                 // +0x18
    p32[7] = 0;                 // +0x1c
    p32[8] = 0;                 // +0x20
    p32[9] = 0;                 // +0x24
    p32[10] = 0;                // +0x28
    p32[11] = 0;                // +0x2c
    p32[12] = 0;                // +0x30
    p32[13] = 0;                // +0x34
    p32[14] = 0;                // +0x38
    p32[15] = 0;                // +0x3c
    p32[16] = 0;                // +0x40
    p32[17] = 0;                // +0x44
    p32[18] = 0;                // +0x48
    p32[19] = 0;                // +0x4c
    p32[20] = 0;                // +0x50
    p32[21] = 0;                // +0x54
    p32[22] = 0;                // +0x58
    p32[23] = 0;                // +0x5c
    p32[24] = 0;                // +0x60
    // Note: offsets 0x64, 0x68, 0x6c are not zeroed in the original code
    p32[28] = 0;                // +0x70
    p32[29] = 0;                // +0x74
    p32[30] = 0;                // +0x78
    p32[31] = 0;                // +0x7c
    p32[32] = 0;                // +0x80
    p32[33] = 0;                // +0x84
    p32[34] = 0;                // +0x88
    p32[35] = 0;                // +0x8c
    p32[36] = 0;                // +0x90
    p32[37] = 0;                // +0x94
}