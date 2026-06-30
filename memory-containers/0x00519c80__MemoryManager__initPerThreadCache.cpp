// FUNC_NAME: MemoryManager::initPerThreadCache

#include <windows.h>

// Global memory manager singleton (DAT_0120541c)
extern void* g_memoryManager;

// Base address used for TLS offset calculation (DAT_01205410)
extern int g_tlsBaseAddress;

// Constant value written to fields 10 and 11 (DAT_00e2b1a4)
extern int g_cacheConstant;

// Forward declarations of internal functions
void* allocateMemory(void* manager, int size); // FUN_00649040
void initializeThreadLocalBlock(); // FUN_006492f0

// Structure representing the per-thread cache block (0x34 bytes = 13 DWORDs)
struct PerThreadCache {
    int field_0;   // +0x00
    int field_1;   // +0x04
    int field_2;   // +0x08
    int field_3;   // +0x0C
    int field_4;   // +0x10
    int field_5;   // +0x14
    int field_6;   // +0x18
    int field_7;   // +0x1C
    int field_8;   // +0x20
    int field_9;   // +0x24
    int constant0; // +0x28
    int constant1; // +0x2C
    int field_12; // +0x30
};

// Outcome returned to caller: offset and success flag
struct ThreadCacheResult {
    int tlsOffset; // offset from g_tlsBaseAddress
    int isInitialized; // 1 on success, 0 on failure
};

// __thiscall? Actually it's a free function using global state
void MemoryManager::initPerThreadCache(ThreadCacheResult* outResult)
{
    int* managerPtr = (int*)g_memoryManager;
    LPCRITICAL_SECTION criticalSection = *(LPCRITICAL_SECTION*)((char*)managerPtr + 0x1b8);

    int offset = 0;
    if (criticalSection != NULL) {
        EnterCriticalSection(criticalSection);
        // Debug-like increment of the critical section's debug info (likely not important)
        criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
            ((int)&(criticalSection[1].DebugInfo)->Type + 1);
    }

    int* allocatedBlock = (int*)allocateMemory(managerPtr, 0x34);
    if (allocatedBlock == NULL) {
        // Allocation failed; fall back to stored pointer at manager+0x17c
        if (criticalSection != NULL) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
                ((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
        offset = *(int*)((char*)managerPtr + 0x17c);
    } else {
        // Initialize the allocated block (likely sets up internal structures)
        initializeThreadLocalBlock();
        // Read some value from the block at offset 8 (e.g., size or pointer)
        offset = *(int*)((char*)allocatedBlock + 8);
        if (criticalSection != NULL) {
            criticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)
                ((int)&criticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(criticalSection);
        }
    }

    int constant = g_cacheConstant;
    if (offset != 0) {
        // Compute the TLS offset relative to the base address
        int tlsOffset = offset - g_tlsBaseAddress;
        // Access the per-thread data via the Thread Environment Block (TEB)
        // TEB+0x2C = ThreadLocalStoragePointer (array of TLS slot pointers)
        // The slot at index 8 is used for this allocator's thread-local data
        void* teb = __readfsdword(0x18); // FS:[0] points to TEB
        int** tlsArray = *(int***)((char*)teb + 0x2C);
        int* tlsSlot = *(int**)((char*)tlsArray + 8);
        PerThreadCache* cache = (PerThreadCache*)((char*)tlsSlot + tlsOffset);
        if (cache != NULL) {
            cache->field_0  = 0;
            cache->field_1  = 0;
            cache->field_2  = 0;
            cache->field_3  = 0;
            cache->field_4  = 0;
            cache->field_5  = 0;
            cache->field_6  = 0;
            cache->field_7  = 0;
            cache->field_8  = 0;
            cache->field_9  = 0;
            cache->constant0 = constant;
            cache->constant1 = constant;
            cache->field_12 = 0;
        }
        outResult->tlsOffset = tlsOffset; // iVar5
    } else {
        outResult->tlsOffset = 0;
    }
    outResult->isInitialized = 1; // param_1[1] = 1
}