// FUNC_NAME: CAnimObjectManager::processFilteredObjects
void CAnimObjectManager::processFilteredObjects(unsigned int uiFilterID)
{
    CAnimObject* pObj = reinterpret_cast<CAnimObject*>(DAT_01205514); // global linked list head

    while (pObj != nullptr)
    {
        if (uiFilterID == 0)
        {
            // Filter matches all objects
            goto process;
        }

        // Compare object's type ID (stored as int at +0xC4 minus 0x48) with filter
        int iTypeID = (pObj->m_pTypeData != nullptr) ? (pObj->m_pTypeData - 0x48) : 0;
        if (uiFilterID == static_cast<unsigned int>(iTypeID))
        {
process:
            // Clear bit 0x100000 (suspected animation completion flag)
            pObj->m_uFlags &= ~0x100000;

            uint uFlags = pObj->m_uFlags;
            if ((uFlags & 0x80000) != 0) // Bit 19: some active state?
            {
                pObj->m_uFlags = uFlags & 0xFFF7FFFF; // Clear bit 19

                // If bit 0 (first flag) is set and parent object has bit 29 set (e.g., visibility?)
                if (((uFlags & 1) != 0) && ((pObj->m_pParent->m_uFlags2 & 0x20000000) != 0))
                {
                    pObj->m_uFlags = (uFlags & 0xFFF7FFFF) | 0x80000000; // Clear bit19, set bit31
                }
                FUN_0051b0b0(pObj); // Process this object (update animation?)
            }
        }

        pObj = pObj->m_pNext; // Linked list traversal
    }
}

// Assumed structure based on offsets
struct CAnimObject
{
    /* +0x00 */ uint32_t m_unk0; // unknown, not used here
    /* +0x04 */ ...;
    /* +0x0C */ uint32_t m_uFlags; // flags: bits 0, 19, 20, 31 relevant
    /* +0x10 */ CAnimObject* m_pParent; // parent object with flags2 at +0x14
    /* +0x14 */ CAnimObject* m_pNext; // linked list next
    // ... other fields ...
    /* +0xC4 */ int* m_pTypeData; // pointer to type data; type ID = m_pTypeData - 0x48
};