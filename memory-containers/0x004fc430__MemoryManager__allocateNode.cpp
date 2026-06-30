// FUNC_NAME: MemoryManager::allocateNode
// Function address: 0x004fc430
// Role: Allocates a node from a global pool and prepares it for use. Returns the node offset and a ready flag.

#include <windows.h>

// Global memory manager instance (offset +0x1b8 contains critical section pointer)
// +0x17c: pointer to last allocated node? (used after allocation)
extern MemoryManager* g_memoryManager; // DAT_0120541c

// Base address for offset calculations (subtracted from node address to get relative index)
extern int g_baseAddress; // DAT_01205410

// Forward declarations of internal functions
void* allocateMemory(int poolIndex, int size); // FUN_00649040 (0xb4 bytes)
void initializeAllocatedBlock(); // FUN_006492f0 (called after successful allocation)
void handleNodeError(); // FUN_004f9a30 (called when node check fails)

void MemoryManager::allocateNode(int* outNode)
{
    CRITICAL_SECTION* critSect = g_memoryManager->m_pCriticalSection; // +0x1b8
    int offset = 0;
    
    if (critSect != nullptr)
    {
        EnterCriticalSection(critSect);
    }
    
    // Attempt to allocate a node of size 0xb4 (180 bytes) from pool
    int allocatedBlock = allocateMemory(g_memoryManager, 0xb4); // g_memoryManager is used as pool index
    
    if (allocatedBlock == 0)
    {
        // Allocation failed; retrieve fallback pointer from +0x17c
        if (critSect != nullptr)
        {
            LeaveCriticalSection(critSect);
        }
        offset = *(int*)((int)g_memoryManager + 0x17c);
    }
    else
    {
        // Allocation succeeded; initialize the block
        initializeAllocatedBlock();
        
        // Read node pointer from offset +8 of the allocated block
        offset = *(int*)(allocatedBlock + 8);
        
        if (critSect != nullptr)
        {
            LeaveCriticalSection(critSect);
        }
    }
    
    // Additional validation using thread-local storage (FS segment)
    if (offset != 0)
    {
        int adjustedOffset = offset - g_baseAddress;
        // TLS check: access current thread's callback table (+0x2c from FS base)
        int** tlsTable = (int**)(__readfsdword(0x2c)); // unaff_FS_OFFSET + 0x2c
        int* callbackEntry = (int*)(tlsTable[0]); // dereference TLS table entry
        int validationValue = callbackEntry[2] + adjustedOffset; // +8 offset from entry? (double dereference)
        if (validationValue != 0)
        {
            handleNodeError();
        }
    }
    
    // Set output: node offset and readiness flag
    outNode[0] = (offset - g_baseAddress); // relative offset
    outNode[1] = 1;                         // ready state
}