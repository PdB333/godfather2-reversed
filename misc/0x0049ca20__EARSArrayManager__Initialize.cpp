// FUNC_NAME: EARSArrayManager::Initialize
undefined4 * EARSArrayManager::Initialize(void)
{
    // +0x00: pointer to allocated array
    // +0x04: count of elements (max 0x4f = 79)
    // +0x08: next free index
    // +0x0c: some other index/state
    g_pData = (void *)0x0;
    g_count = 0x4f;
    g_nextFree = 0;
    g_otherIndex = 0;
    g_pData = (void *)FUN_009c8e80(0x13c);  // allocate 0x13c bytes (79 * 4)
    _memset(g_pData, 0, g_count * 4);
    return &g_pData;
}