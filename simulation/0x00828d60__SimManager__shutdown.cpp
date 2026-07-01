//FUNC_NAME: SimManager::shutdown
void __fastcall SimManager::shutdown(SimManager* thisPtr)
{
    // Iterate over all objects in the simulation hash table
    int* pBucket = (int*)SimManager::sm_pObjectHashTable; // PTR_DAT_00e53e88
    int currentObject = *pBucket;
    if (currentObject == 0)
    {
        pBucket = (int*)((int)SimManager::sm_pObjectHashTable + 4);
        currentObject = *pBucket;
        while (currentObject == 0)
        {
            pBucket++;
            currentObject = *pBucket;
        }
        currentObject = *pBucket;
    }
    int endMarker = *(int*)((int)SimManager::sm_pObjectHashTable + SimManager::sm_objectCount * 4); // DAT_00e53e8c

    while (currentObject != endMarker)
    {
        SimObject* obj = *(SimObject**)(currentObject + 4); // +0x4: object pointer
        if (obj->field_0x1C != 0) // offset 0x1C (puVar3[7])
        {
            FUN_004aa750(); // cleanup function (likely object-specific)
        }
        obj->vtable->method0(1); // virtual function at vtable[0] with arg 1
        currentObject = *(int*)(currentObject + 8); // next node in bucket
        while (currentObject == 0)
        {
            pBucket++;
            currentObject = *pBucket;
        }
    }

    // Free the hash table memory
    FUN_008285c0(SimManager::sm_pObjectHashTable, SimManager::sm_objectCount);
    SimManager::sm_someFlag = 0; // DAT_00e53e90

    // Reset global state
    FUN_004086d0(&DAT_0112db7c);
    FUN_008285c0(SimManager::sm_pObjectHashTable, SimManager::sm_objectCount);
    SimManager::sm_someFlag = 0;

    if (SimManager::sm_objectCount > 1)
    {
        FUN_009c8f10(SimManager::sm_pObjectHashTable);
    }

    // Save some global values
    SimManager::sm_savedValue1 = _DAT_00d5780c;
    SimManager::sm_savedValue2 = DAT_00d5eee4;
    SimManager::sm_objectCount = 1;
    SimManager::sm_pObjectHashTable = (undefined*)&DAT_00ef4398;
    SimManager::sm_someFlag = 0;
    SimManager::sm_savedValue3 = 0;

    // Second list cleanup (similar pattern)
    FUN_008285c0(SimManager::sm_pAnotherList, SimManager::sm_anotherCount);
    SimManager::sm_anotherFlag = 0;
    if (SimManager::sm_anotherCount > 1)
    {
        FUN_009c8f10(SimManager::sm_pAnotherList);
    }
    SimManager::sm_anotherSaved1 = _DAT_00d5780c;
    SimManager::sm_anotherSaved2 = DAT_00d5eee4;
    SimManager::sm_anotherCount = 1;
    SimManager::sm_pAnotherList = (undefined*)&DAT_00ef4398;
    SimManager::sm_anotherFlag = 0;
    SimManager::sm_anotherSaved3 = 0;

    // Final cleanup
    FUN_004083d0();

    // Restore vtable pointer (destructor epilogue)
    thisPtr->vtable = &PTR_LAB_00d735b4; // set to base class vtable
    DAT_0112db98 = 0;
}