// FUNC_NAME: SimManager::addSimObject
void __thiscall SimManager::addSimObject(int thisPtr, uint objectId, int param3)
{
    uint flags = *(uint *)(thisPtr + 0x54);
    bool isFlag30Clear = (flags >> 0x1e & 1) == 0;
    if (!isFlag30Clear) return;

    if ((param3 != 0) || ((*(byte *)(thisPtr + 0x54) & 1) == 0) || (FUN_0080f980(objectId) == 0))
    {
        if (FUN_008eadd0(objectId) == 0)
        {
            // Not a special resource type; try to load from cache
            int* cacheEntry = nullptr;
            int data = FUN_004461c0(objectId, 0);
            if (data != 0)
            {
                param3 = 0;
                param3 = FUN_00446130(objectId, 0);
                bool valid = FUN_0080f5d0(param3, 0x647df06b, &objectId);
                if (valid)
                {
                    *(uint *)(thisPtr + 0x54) |= 0x20000000; // set loading flag
                    FUN_008cff70(thisPtr, &param3);
                }
                if (param3 != 0)
                {
                    FUN_00475660(param3, 0x38523fc3, &cacheEntry);
                    int* entry = cacheEntry;
                    if (cacheEntry != nullptr)
                    {
                        // Call virtual functions on sub-objects
                        (**(code **)(*cacheEntry + 0x20))(thisPtr + 0xc0);
                        (**(code **)(*entry + 0x1c))(thisPtr + 0x100);
                        FUN_0045ca00(entry);
                        FUN_0045c400(thisPtr + 0xb0, &stack0xffffffec, 0);
                        if ((*(uint *)(thisPtr + 0x54) >> 1 & 1) != 0)
                        {
                            FUN_0080f840(entry);
                        }
                        if (cacheEntry != nullptr)
                        {
                            FUN_004daf90(&cacheEntry);
                        }
                    }
                }
            }
        }
        else
        {
            // Resource type requiring streaming
            *(uint *)(thisPtr + 0x54) |= 0x40000000; // set streaming flag
            bool streamResult = FUN_008f0bb0(objectId, -1, thisPtr, 0);
            if (!streamResult)
            {
                *(uint *)(thisPtr + 0x54) &= 0xbfffffff; // clear streaming flag
                return;
            }
        }
    }
}