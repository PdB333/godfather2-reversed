// FUNC_NAME: HandleManager::applyCommand
void __thiscall HandleManager::applyCommand(void* pResourceArray, uint32 someID)
{
    // +0x00: byte m_byteField
    // +0x04: int m_intField
    uint32 handle = resolveHandle(pResourceArray, someID, this);
    if (handle != 0 && (handle & 0xFFFF) < 0x200)
    {
        uint32 index = handle & 0xFFFF;
        // Each resource entry is 0x30 bytes, array starts at pResourceArray + 0x10
        ResourceEntry* pEntry = (ResourceEntry*)((uint8*)pResourceArray + 0x10 + index * 0x30);
        if (pEntry != 0 && pEntry->id == handle)
        {
            uint32 byteField = this->m_byteField;
            uint32 intField = this->m_intField;
            if (pEntry != 0) // redundant check
            {
                pEntry->state = 2;
                // Write to the target object pointed by pEntry->pObject
                if (pEntry->pObject != 0)
                {
                    // Target object offsets: +0x58 (byte), +0x5A (short)
                    *(uint8*)((uint8*)pEntry->pObject + 0x58) = (uint8)byteField;
                    *(int16*)((uint8*)pEntry->pObject + 0x5A) = (int16)intField;
                }
            }
        }
    }
}

// Supporting struct definitions (assumed)
struct ResourceEntry
{
    uint8 _pad0[0x10];       // +0x10
    void* pObject;           // +0x10
    int state;               // +0x18
    uint8 _pad1[0x10];       // +0x1C to 0x2B
    uint32 id;               // +0x2C
};