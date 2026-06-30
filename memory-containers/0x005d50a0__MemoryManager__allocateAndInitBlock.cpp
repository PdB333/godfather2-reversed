// FUNC_NAME: MemoryManager::allocateAndInitBlock
// Address: 0x005d50a0
// Role: Allocates a 4-byte aligned block from a memory pool (cursor at global g_MemoryManager + 0x14),
// writes a vtable pointer (PTR_LAB_01126b68) and a flag value (1). Used for small object construction.
void MemoryManager::allocateAndInitBlock(void)
{
    int *pCursor;                  // pointer to the pool cursor at g_MemoryManager + 0x14
    undefined4 *pAligned;          // aligned write target

    pCursor = (int *)(g_MemoryManager + 0x14);                     // +0x14: current allocation cursor
    *(void **)(g_MemoryManager + 0x14) = &PTR_LAB_01126b68;        // set vtable at cursor position
    *pCursor = *pCursor + 4;                                       // advance cursor past vtable pointer

    // align next write to 4-byte boundary
    pAligned = (undefined4 *)((*pCursor + 3U) & 0xfffffffc);
    *pCursor = (int)pAligned;

    *pAligned = 1;                                                 // write flag byte (1 = initialized)
    *pCursor = *pCursor + 4;                                       // advance cursor past the written value
    return;
}