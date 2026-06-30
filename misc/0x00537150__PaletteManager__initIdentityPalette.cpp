// FUNC_NAME: PaletteManager::initIdentityPalette

void PaletteManager::initIdentityPalette(void)
{
    // External globals typically defined elsewhere
    extern void* g_pPaletteMemoryManager; // DAT_01198e20: pointer to a memory buffer manager with vtable
    extern ushort* g_pStaticPaletteBuffer; // DAT_01198e30: static fallback buffer
    extern bool g_bUseDynamicBuffer; // DAT_01198e3c: 0 = use static, 1 = use dynamic from manager
    extern bool g_bPaletteInitialized; // DAT_01198e3d: flag for static case
    extern bool g_bSomeFlag; // DAT_01198e2c: influences allocation size (0x3000 addition)

    ushort* pDst;
    
    // Initialize underlying memory manager with allocation size, alignment, etc.
    // FUN_0060b620 is likely MemoryManager::init or similar (0x800 bytes, alignment 0x12)
    MemoryManager::init(0x800, 0, &g_pPaletteMemoryManager, 0x12); // parameters: size, flags, outManager, param

    if (!g_bUseDynamicBuffer) {
        // Use static buffer path
        g_bPaletteInitialized = true;
        pDst = g_pStaticPaletteBuffer;
    }
    else {
        // Use dynamic buffer from memory manager
        unsigned int allocFlags = 0;
        if (g_bSomeFlag) {
            allocFlags = 0x3000;
        }
        // vtable call at offset 0x2c: lock or get pointer to buffer
        typedef void* (__thiscall *LockBufferFunc)(void* self, int, int, ushort**, unsigned int);
        LockBufferFunc pLock = *(LockBufferFunc*)(*(void**)g_pPaletteMemoryManager + 0x2c);
        pLock(g_pPaletteMemoryManager, 0, 0, &pDst, allocFlags);
    }

    // Clear buffer to zero
    _memset(pDst, 0, 0x800);

    // Fill with identity mapping: 0, 1, ..., 0x1FF (512 ushorts)
    ushort value = 0;
    do {
        *pDst = value;
        value = value + 1;
        pDst = pDst + 1; // Move to next ushort (each increment is 2 bytes)
    } while (value < 0x200); // 0x200 = 512 entries

    if (g_bUseDynamicBuffer) {
        // vtable call at offset 0x30: unlock or release buffer
        typedef void (__thiscall *UnlockBufferFunc)(void* self);
        UnlockBufferFunc pUnlock = *(UnlockBufferFunc*)(*(void**)g_pPaletteMemoryManager + 0x30);
        pUnlock(g_pPaletteMemoryManager);
        return;
    }

    g_bPaletteInitialized = false;
}