// FUNC_NAME: EntityContainer::syncActiveObjectsFromGlobalList

void __thiscall EntityContainer::syncActiveObjectsFromGlobalList()
{
    int globalCount = g_globalListCount;                                // +0x01163edc
    char* marker = (char*)_alloca(globalCount);                        // per-slot keep flag
    _memset(marker, 0, globalCount);
    int keptCount = 0;                                                 // number of slots to keep (marked)

    int ownCount = *(int*)((char*)this + 0x34);                        // +0x34: number of own objects
    if (ownCount != 0)
    {
        char* objPtr = *(char**)((char*)this + 0x50);                  // +0x50: pointer to first object (stride 0xB0)
        for (int i = 0; i < ownCount; ++i)
        {
            if (*(objPtr + 8) & 0x20)                                  // +0x08: flags, 0x20 = active
            {
                for (int j = 0; j < globalCount; ++j)
                {
                    if (*(int*)(g_globalListArray + j * 8) == (int)objPtr) // +0x01163ee0: array of {ptr, tag}
                    {
                        marker[j] = 1;
                        ++keptCount;
                        break;
                    }
                }
            }
            objPtr += 0xB0;                                            // object size
        }
    }

    // compact global list: remove entries that are NOT marked (i.e. not in own active set)
    int writeIdx = 0;
    for (int readIdx = 0; readIdx < globalCount; ++readIdx)
    {
        if (marker[readIdx] != 0)                                      // keep this slot
        {
            if (writeIdx != readIdx)
            {
                *(int*)(g_globalListArray + writeIdx * 8) = *(int*)(g_globalListArray + readIdx * 8);
                *(int*)(g_globalListArray + writeIdx * 8 + 4) = *(int*)(g_globalListArray + readIdx * 8 + 4);
            }
            ++writeIdx;
        }
    }
    g_globalListCount = keptCount;                                     // update to new size
}