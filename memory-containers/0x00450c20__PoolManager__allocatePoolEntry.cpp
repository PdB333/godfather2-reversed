// FUNC_NAME: PoolManager::allocatePoolEntry
// WARNING: This function uses FS segment for TLS (Thread Local Storage)
// Address: 0x00450c20
// Purpose: Allocate a 0x14130-byte pool block, initialize it, and output its offset from global base.

struct PoolEntry {
    int offset;      // +0x00: offset from global base
    int initialized; // +0x04: flag (set to 1 on success)
};

// Forward declarations for helper functions (internal EA allocator)
int allocatePoolBlock(void* poolManager, int size);     // 0x00649040
void initPoolBlock(void* block);                       // 0x006492f0

// Global data (from binary)
extern int g_poolManager;           // DAT_0120541c
extern int g_globalBase;            // DAT_01205410

void PoolManager::allocatePoolEntry(PoolEntry* outEntry)
{
    LPCRITICAL_SECTION criticalSection;
    int iVar1;
    int iVar2;
    int iVar3;
    int* pTlsSlot = (int*)__readfsdword(0x2c); // TLS base

    iVar2 = g_poolManager;
    criticalSection = *(LPCRITICAL_SECTION*)(g_poolManager + 0x1b8); // global critical section
    iVar3 = 0;

    if (criticalSection != nullptr) {
        EnterCriticalSection(criticalSection);
        // Bit manipulation on DebugInfo is likely a lock flag increment (thread-safe refcount)
        criticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }

    // Allocate a 0x14130-byte block from the pool manager
    iVar1 = allocatePoolBlock(iVar2, 0x14130);
    if (iVar1 == 0) {
        // Failed: use fallback pointer from pool manager +0x17c
        if (criticalSection != nullptr) {
            // Decrement lock flag
            criticalSection[1].DebugInfo =
                (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
        iVar2 = *(int*)(iVar2 + 0x17c); // fallback pool base
    }
    else {
        // Success: initialize the block
        initPoolBlock(iVar1);
        iVar2 = *(int*)(iVar1 + 8); // likely pointer to block data inside the allocation
        if (criticalSection != nullptr) {
            criticalSection[1].DebugInfo =
                (PRTL_CRITICAL_SECTION_DEBUG)((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
    }

    // Compute offset from global base
    if (iVar2 != 0) {
        iVar3 = iVar2 - g_globalBase;
        // Get TLS data: deref *(pTlsSlot) + 8, then add offset, zero out fields
        int* pTlsData = *(int**)(*(int*)(pTlsSlot + 0x2c) + 8) + iVar3; // adjust for TLS structure
        if (pTlsData != nullptr) {
            // Zero out several fields at offsets:
            *(int*)(pTlsData + 4) = 0;
            *(int*)(pTlsData + 0x88) = 0;
            *(int*)(pTlsData + 0x10c) = 0;
            *(int*)(pTlsData + 0x4110) = 0;
            *(int*)(pTlsData + 0x14120) = 0;
        }
    }

    // Output the pool entry
    outEntry->offset = iVar3;
    outEntry->initialized = 1;
}