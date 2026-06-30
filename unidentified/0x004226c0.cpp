// FUN_NAME: MemoryPool::freeElement
void __fastcall MemoryPool::freeElement(void* pObject)
{
    // Get thread-local data (FS:[0x2c] points to a per-thread structure)
    ThreadLocalData* pThreadData = *(ThreadLocalData**)__readfsdword(0x2c);

    // Check if the thread's free list is empty (offset +0x34?)
    if (pThreadData->field_0x34 == 0)
    {
        // Global free list head pointer at DAT_01206880+0x14
        int** ppListHead = (int**)(g_pGlobalPtr + 0x14); // DAT_01206880 is likely a global struct
        // Push the object onto a global stack-like list
        *(void**)(*ppListHead) = (void*)&g_freeListHead; // PTR_LAB_0110b62c is a sentinel or next pointer
        *ppListHead = *ppListHead + 4;
        *(void**)(*ppListHead) = pObject;
        *ppListHead = *ppListHead + 4;
    }

    // If the thread's current object (offset +0x24) matches this object, clear it
    if (pThreadData->field_0x24 == pObject)
    {
        pThreadData->field_0x24 = 0;
    }

    // Free the sub-object pointed to by offset +0x178
    int* pSubObject = *(int**)((char*)pObject + 0x178);
    if (pSubObject != 0)
    {
        int* pData = *(int**)((char*)pSubObject + 4);
        if (pData != 0)
        {
            // Call destructor for the data block (size 0x30, with vtable/function pointer)
            sub_Destructor(pData, 0x30, *(uint*)((char*)pData - 4), &g_subVtable);
            sub_FreeMemory((char*)pData - 4);
        }
        sub_FreeSubObject(pSubObject);
    }

    // Lock mutex at DAT_00e2e6f8
    EnterCriticalSection(&g_poolMutex);

    // Mark the slot as free in the pool array at DAT_012053b4
    // Index = (pObject - g_poolBase) / 0x180
    int index = ((int)pObject - (int)&g_poolBase) / 0x180;
    g_poolSlots[index] = 0;

    // Unlock mutex
    LeaveCriticalSection(&g_poolMutex);
}