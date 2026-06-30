// FUNC_NAME: CacheManager::updateCachedBlock
void __fastcall CacheManager::updateCachedBlock(int unused, int count, byte* source)
{
    // Global cache tables: read cache (0x011d97f0), write cache (0x011ea8f0)
    // The flags register (EAX) encodes: low byte = cache index, second byte = block size multiplier (in 16-byte units), sign bit = cache type (0=read, 1=write)
    unsigned int flags; // in_EAX (implicit register parameter)

    if (flags == 0)
        return;

    // Decompose flags
    unsigned int cacheIndex = flags & 0xFF;
    unsigned int blockSizeCount = (flags >> 8) & 0xFF;
    int totalBlockSize = blockSizeCount * count; // Note: iVar7 = uVar6 * param_2
    bool useWriteCache = (flags & 0x80000000) != 0;
    byte* cacheBase = useWriteCache ? &g_writeDataCache : &g_readDataCache; // DAT_011ea8f0 vs DAT_011d97f0
    byte* entryPtr = cacheBase + cacheIndex * 0x10;  // Each cache slot is 0x10 bytes
    size_t copySize = blockSizeCount * 0x10;         // Copy size per iteration

    bool changed = false;
    byte* dst = entryPtr;
    byte* src = source;

    for (int i = 0; i < count; i++)
    {
        if (changed)
        {
            // Already known different, just copy
            memcpy(dst, src, copySize);
        }
        else
        {
            // Compare first, only copy if different
            if (memcmp(dst, src, copySize) != 0)
            {
                memcpy(dst, src, copySize);
                changed = true;
            }
        }
        src += 0x40;   // Source stride: 64 bytes
        dst += copySize;
    }

    if (changed)
    {
        // Notify manager (global object at DAT_01205750) via virtual function
        // Vtable offsets: 0x178 for write cache, 0x1b4 for read cache
        if (useWriteCache)
        {
            (**(code**)(*g_cacheManager + 0x178))(g_cacheManager, cacheIndex, entryPtr, totalBlockSize);
        }
        else
        {
            (**(code**)(*g_cacheManager + 0x1b4))(g_cacheManager, cacheIndex, entryPtr, totalBlockSize);
        }
    }
}