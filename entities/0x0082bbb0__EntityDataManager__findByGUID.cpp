// FUNC_NAME: EntityDataManager::findByGUID
int __thiscall EntityDataManager::findByGUID( EntityDataManager* this, const int* guid )
{
    // +0x08: pointer to array of entity pointers
    // +0x0C: number of entities in array
    uint count = *(uint*)((int)this + 0xC);
    if ( count != 0 )
    {
        int** entityArray = *(int***)((int)this + 0x8);
        for ( uint i = 0; i < count; i++ )
        {
            int* entityPtr = entityArray[i];
            // Each entity has GUID stored as 4 ints at offsets +0x1C, +0x20, +0x24, +0x28
            if ( entityPtr[0x1C/4] == guid[0] &&
                 entityPtr[0x20/4] == guid[1] &&
                 entityPtr[0x24/4] == guid[2] &&
                 entityPtr[0x28/4] == guid[3] )
            {
                return (int)entityPtr;
            }
        }
    }
    return 0;
}