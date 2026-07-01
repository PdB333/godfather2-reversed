// FUNC_NAME: ResourceManager::releaseReference
void __thiscall ResourceManager::releaseReference(int param_2)
{
    bool bIsCurrentResource;
    int iCurrentResourceId;
    int iVar2;
    char cVar3;
    int iVar4;
    uint uIndex;
    int *piEntryPtr;

    iVar2 = DAT_01129904; // some global
    bIsCurrentResource = false;

    // Check if there is a single entry and it matches some special condition (active resource?)
    if ((this->entriesCount == 1) && (((Entry*)this->entriesArray)->field1 == *(int*)(this->vtablePtr + 4)))
    {
        iCurrentResourceId = *(int*)this->entriesArray;
    }
    else
    {
        iCurrentResourceId = 0;
    }

    if (iCurrentResourceId == param_2)
    {
        bIsCurrentResource = true;
        cVar3 = canReleaseResource(); // FUN_0084a670
        if (cVar3 != 0)
        {
            releaseResource(param_2, this->vtablePtr); // FUN_008c78f0
        }

        // Special case: specific resource ID and global conditions
        if ((param_2 == 0x637b907) && (*(char*)(iVar2 + 0x3c) != 0) && 
            (*(char*)(DAT_0112a590 + 4) != 0))
        {
            playUISound(0x21); // FUN_007e7df0
        }
    }

    // Find the entry with matching ID
    uIndex = 0;
    if (this->entriesCount != 0)
    {
        piEntryPtr = (int*)this->entriesArray;
        do
        {
            if (*piEntryPtr == param_2) goto LAB_0084a7c1;
            uIndex = uIndex + 1;
            piEntryPtr = piEntryPtr + 2;
        } while (uIndex < (uint)this->entriesCount);
    }
    uIndex = 0xffffffff;

LAB_0084a7c1:
    // Decrement reference count of the found entry (second int in struct)
    piEntryPtr = (int*)(this->entriesArray + 4 + uIndex * 8);
    *piEntryPtr = *piEntryPtr - 1;

    if (*piEntryPtr == 0)
    {
        removeEntry(uIndex); // FUN_0084a1e0
    }
    else if (1 < (uint)this->entriesCount)
    {
        qsort((void*)this->entriesArray, this->entriesCount, 8, (_PtFuncCompare*)&entryCompare); // 0x0084a120
    }

    // If this was the current resource and there are pending callbacks, invoke them
    if ((bIsCurrentResource) && (this->callbackCount != 0))
    {
        uIndex = 0;
        do
        {
            invokeCallback(); // FUN_006b3220
            uIndex = uIndex + 1;
        } while (uIndex < (uint)this->callbackCount);
    }
    return;
}