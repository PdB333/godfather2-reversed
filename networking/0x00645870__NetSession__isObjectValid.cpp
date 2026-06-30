// FUNC_NAME: NetSession::isObjectValid
bool NetSession::isObjectValid(void* pObject) // pObject passed in EDI
{
    LPCRITICAL_SECTION pCriticalSection = *(LPCRITICAL_SECTION*)(this + 0x4e8); // m_pCriticalSection
    if (pCriticalSection != (LPCRITICAL_SECTION)0x0)
    {
        EnterCriticalSection(pCriticalSection);
        // Debug: adjust critical section internal fields (EA internal debug hook)
        pCriticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&(pCriticalSection[1].DebugInfo)->Type + 1);
    }

    // Extract type flag from object's vtable-like structure at +0x4
    uint32_t typeFlag = *(uint32_t*)((*(uint32_t*)((uint32_t)pObject + 4) & 0x7ffffff8) + 4 + (uint32_t)pObject) & 1;

    bool bValid;
    if (typeFlag == 0)
    {
        bValid = (validateType0(pObject) == 0);
    }
    else
    {
        bValid = (validateType1(pObject) == 0);
    }

    if (bValid)
    {
        // Additional check: for type 0 objects that are self-referencing (pObject+0xc points to itself)
        bool bExcludeCondition = false;
        if ((typeFlag == 0) && (pObject == *(void**)((uint32_t)pObject + 0xc))) // +0xc is self-pointer or list marker
        {
            bExcludeCondition = (pObject != *(void**)(this + 0x440)); // m_pExcludedObject
        }
        bValid = !bExcludeCondition;
    }

    if (pCriticalSection != (LPCRITICAL_SECTION)0x0)
    {
        // Revert the debug hack
        pCriticalSection[1].DebugInfo =
            (PRTL_CRITICAL_SECTION_DEBUG)((int)&pCriticalSection[1].DebugInfo[-1].SpareWORD + 1);
        LeaveCriticalSection(pCriticalSection);
    }

    return bValid;
}