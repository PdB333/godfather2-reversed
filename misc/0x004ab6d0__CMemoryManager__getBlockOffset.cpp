// FUNC_NAME: CMemoryManager::getBlockOffset
extern CMemoryManager* g_memoryManager; // DAT_0120541c
extern int g_baseAddress; // DAT_01205410

extern void* allocBlockFromPool(CMemoryManager* mgr, int size); // FUN_00649040
extern void initAllocatedBlock(void* block); // FUN_006492f0

struct CMemoryManager {
    // +0x17c: int* fallbackListPtr;
    // +0x1b8: CRITICAL_SECTION lock;
};

void CMemoryManager::getBlockOffset(int* outResult) {
    CRITICAL_SECTION* critSect = (CRITICAL_SECTION*)((char*)g_memoryManager + 0x1b8);
    int* dataPtr = nullptr;

    EnterCriticalSection(critSect);

    void* newBlock = allocBlockFromPool(g_memoryManager, 0xA0);
    if (newBlock != nullptr) {
        initAllocatedBlock(newBlock);
        dataPtr = *(int**)((char*)newBlock + 8);
    } else {
        dataPtr = *(int**)((char*)g_memoryManager + 0x17c);
    }

    LeaveCriticalSection(critSect);

    int offset = 0;
    if (dataPtr != nullptr) {
        offset = (int)dataPtr - g_baseAddress;
    }
    outResult[0] = offset;
    outResult[1] = 1; // success flag
}