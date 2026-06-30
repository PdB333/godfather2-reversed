// FUNC_NAME: MemoryChunk::initSentinel
void MemoryChunk::initSentinel(void)
{
    uint32_t* fields = (uint32_t*)this;
    uint32_t poolBase  = DAT_00e2eff4;  // global pool base pointer
    uint32_t poolLimit = DAT_00e2b1a4;  // global pool limit pointer

    // +0x00: pool base (triple copy for alignment checks)
    fields[0] = poolBase;
    fields[1] = poolBase;
    fields[2] = poolBase;

    // +0x0C: pool limit (double copy)
    fields[3] = poolLimit;
    fields[4] = poolLimit;

    // +0x14: flags (0 = free)
    fields[5] = 0;
    // +0x18: reserved
    fields[6] = 0;
    // +0x1C: allocation count (1 = allocated)
    fields[7] = 1;

    // +0x20..+0x2F: debug sentinels
    fields[8]  = 0xBADBADBA;
    fields[9]  = 0xBEEFBEEF;
    fields[10] = 0xEAC15A55;
    fields[11] = 0x91100911;

    // +0x30: clear low byte of sentinel dword (marks start of user data)
    *(uint8_t*)(fields + 12) = 0;

    // +0x34: user data size hint (96000 = ~96 KB)
    fields[13] = 96000;
}