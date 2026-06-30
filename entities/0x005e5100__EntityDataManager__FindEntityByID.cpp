// FUNC_NAME: EntityDataManager::FindEntityByID
int __fastcall EntityDataManager::FindEntityByID(void* unused, EntityDataManager* __this, int entityID)
{
    uint count = *(uint*)((int)__this + 0x6018);
    if (count == 0)
    {
        return 0;
    }

    int** entryArray = *(int***)((int)__this + 0x6014);
    uint i = 0;
    while (i < count)
    {
        int* entry = entryArray[i];
        if (entry != nullptr && *(int*)(entry + 4) == entityID)
        {
            return (int)entry;
        }
        i++;
    }
    return 0;
}