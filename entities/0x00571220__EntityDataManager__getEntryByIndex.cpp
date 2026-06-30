// FUNC_NAME: EntityDataManager::getEntryByIndex
short sIndex;
int* pDataManager;
int* pArray;

pDataManager = *(int**)(this + 0x70); // m_pDataManager
if (pDataManager != nullptr &&
    *(int*)(pDataManager + 0x18) > 0 &&   // m_entryCount
    *(int**)(pDataManager + 0x1c) != nullptr) // m_pEntries
{
    sIndex = *(short*)(this + 0x76); // m_currentIndex
    if (sIndex >= 0 && (int)sIndex < *(int*)(pDataManager + 0x18))
    {
        // Each entry is 0x18 bytes
        return *(int**)(pDataManager + 0x1c) + sIndex * 0x18;
    }
}
return nullptr;

int __thiscall EntityDataManager::getEntryByIndex(void)
{
    short sIndex;
    int* pDataManager;
    int* pArray;

    pDataManager = *(int**)(this + 0x70); // m_pDataManager
    if (pDataManager != nullptr &&
        *(int*)(pDataManager + 0x18) > 0 &&   // m_entryCount
        *(int**)(pDataManager + 0x1c) != nullptr) // m_pEntries
    {
        sIndex = *(short*)(this + 0x76); // m_currentIndex
        if (sIndex >= 0 && (int)sIndex < *(int*)(pDataManager + 0x18))
        {
            // Each entry is 0x18 bytes
            return (int)(*(int**)(pDataManager + 0x1c) + sIndex * 0x18);
        }
    }
    return 0;
}