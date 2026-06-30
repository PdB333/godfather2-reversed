// FUNC_NAME: SimObject::~SimObject
void __fastcall SimObject::~SimObject(void)
{
    // Step 1: Set vtable to destructor-specific vtable (to prevent virtual calls during destruction)
    this->vftable = &g_DestructorVtable1;

    // Step 2: Iterate over the global object list and remove any references to this object
    //         from other objects' sub-reference arrays.
    SimObject* pObj = g_pObjectList;
    while (pObj)
    {
        if (pObj->m_pSubRefArray != nullptr)
        {
            int count = pObj->m_subRefCount;
            for (int i = 0; i < count; i++)
            {
                SubReference* pRef = pObj->m_pSubRefArray + i;
                // Check if this reference is active and points to 'this'
                if ((pRef->flags & 1) == 0 && pRef->pTarget == this)
                {
                    // Copy current frame data from thread‑local storage into the reference
                    uint32_t* pTLS = *(uint32_t**)(*(uint32_t**)(__readfsdword(0x2CU) + 0x8) + 0x4);
                    uint32_t* pSrc = (uint32_t*)((uint8_t*)pTLS + 0x80) + pRef->someIndex; // puVar1+0x80+puVar1[4]
                    pRef->vec.x = pSrc[0];
                    pRef->vec.y = pSrc[1];
                    pRef->vec.z = pSrc[2];
                    pRef->vec.w = pSrc[3];
                    // Clear the target pointer so the reference no longer points to us
                    pRef->pTarget = nullptr;
                }
            }
        }
        pObj = pObj->m_pNext;
    }

    // Step 3: Release own sub-reference array (if any)
    if (this->m_pSubRefArray != nullptr)
    {
        for (int i = 0; i < this->m_subRefCount; i++)
        {
            SubReference* pRef = this->m_pSubRefArray + i;
            if (pRef->pObj != nullptr)
            {
                // Call virtual release (vtable+4) on the referenced object
                (*(code**)(*(int*)g_SomeGlobalVtable + 4))(pRef->pObj, 0);
            }
            // Call deallocation helper (likely free())
            FUN_004fd2c0();
        }
        // Release the array container itself
        (*(code**)(*(int*)g_SomeGlobalVtable + 4))(this->m_pSubRefArray, 0);
    }

    // Step 4: If the flag is set, push 'this' onto a global free list
    if (this->m_flag != 0)
    {
        // Append to a singly‑linked free list stored in a global buffer
        uint32_t* pBuffer = (uint32_t*)(g_GlobalBuffer + 0x14);
        *pBuffer = (uint32_t)&g_FreeListVtable1;
        pBuffer[1] = (uint32_t)this;
        g_GlobalBuffer += sizeof(uint32_t);
    }

    // Step 5: Transition to base‑class vtable (end of derived destruction)
    this->vftable = &g_BaseVtable;

    // Step 6: Free an allocated memory block (if present), again via a global free list
    if (this->m_pAllocatedMem != nullptr)
    {
        uint32_t* pBuffer = (uint32_t*)(g_GlobalBuffer + 0x14);
        *pBuffer = (uint32_t)&g_FreeListVtable2;
        pBuffer[1] = (uint32_t)this->m_pAllocatedMem;
        g_GlobalBuffer += sizeof(uint32_t);
        this->m_pAllocatedMem = nullptr;
        this->m_allocatedSize = 0;
    }

    // Step 7: Remove 'this' from the global linked list (singly linked)
    SimObject** ppPrev = &g_pObjectList;
    SimObject* pCur = *ppPrev;
    while (pCur)
    {
        if (pCur == this)
        {
            *ppPrev = this->m_pNext;
            break;
        }
        ppPrev = &pCur->m_pNext;
        pCur = *ppPrev;
    }
}