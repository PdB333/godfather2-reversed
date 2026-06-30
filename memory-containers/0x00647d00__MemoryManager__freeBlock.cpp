// FUNC_NAME: MemoryManager::freeBlock
uint __thiscall MemoryManager::freeBlock(void *this, void *ptr)
{
    LPCRITICAL_SECTION critSec;
    uint blockSize;

    critSec = *(LPCRITICAL_SECTION *)((int)this + 0x4e8);
    if (critSec != (LPCRITICAL_SECTION)0x0) {
        EnterCriticalSection(critSec);
        // Use the DebugInfo of the next CRITICAL_SECTION as a reference count or flag.
        critSec[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&(critSec[1].DebugInfo)->Type + 1);
    }
    blockSize = *(uint *)((int)ptr + -4);
    if (critSec != (LPCRITICAL_SECTION)0x0) {
        critSec[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&critSec[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(critSec);
    }
    return blockSize & 0x7ffffff8;
}