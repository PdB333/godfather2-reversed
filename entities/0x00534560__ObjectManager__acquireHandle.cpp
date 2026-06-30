// FUNC_NAME: ObjectManager::acquireHandle
#include <windows.h>

// Global memory manager singleton
extern void* g_pMemoryManager; // = DAT_0120541c
extern void* g_pPoolBase;      // = DAT_01205410

// Forward declarations of internal helpers
void* allocateMemory(void* manager, uint32_t size); // FUN_00649040
void  initializeMemory(void* block);                // FUN_006492f0
void  notifyHandleAvailable(void* handle);          // FUN_00533ab0

// Acquires a handle to a pooled object, writing (offset, 1) to outHandle.
void ObjectManager::acquireHandle(int* outHandle) // param_1
{
    CRITICAL_SECTION* pCriticalSection;
    int handleValue;
    void* allocatedBlock;
    void* objectPointer;

    pCriticalSection = *(CRITICAL_SECTION**)((uint8_t*)g_pMemoryManager + 0x1b8);
    if (pCriticalSection != nullptr)
    {
        EnterCriticalSection(pCriticalSection);
        // Increment the resource counter (stored in a debug field, repurposed)
        pCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&(pCriticalSection[1].DebugInfo)->Type + 1);
    }

    allocatedBlock = allocateMemory(g_pMemoryManager, 0x90);
    if (allocatedBlock == nullptr)
    {
        if (pCriticalSection != nullptr)
        {
            // Decrement resource counter
            pCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(pCriticalSection);
        }
        objectPointer = *(void**)((uint8_t*)g_pMemoryManager + 0x17c); // fallback pointer
    }
    else
    {
        initializeMemory(allocatedBlock);
        objectPointer = *(void**)((uint8_t*)allocatedBlock + 8);
        if (pCriticalSection != nullptr)
        {
            pCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
            LeaveCriticalSection(pCriticalSection);
        }
    }

    // Calculate handle as offset from pool base; if non-null and address mismatch, call notification
    if (objectPointer != nullptr)
    {
        handleValue = (int)objectPointer - (int)g_pPoolBase;
        // Check if object pointer is within the same module (FSEG:0x2c + 8)
        if (*(int*)(**(int**)(__readfsdword(0x2c)) + 8) + handleValue != 0)
        {
            notifyHandleAvailable(objectPointer);
        }
    }
    else
    {
        handleValue = 0;
    }

    outHandle[0] = handleValue;  // offset from pool base
    outHandle[1] = 1;            // reference count / type marker
}