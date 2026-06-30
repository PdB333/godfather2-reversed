// FUNC_NAME: SimObject::resolveReference
void __thiscall SimObject::resolveReference(SimObject* thisPtr, int entityId, CollectionContainer* collection, undefined4 arg4, undefined4 arg5)
{
    int iVar1;
    undefined4* refCountedObj;
    int iVar3;
    int* pEntityArray;

    // Call some initialization/check
    unknownInitializationFunction();

    // Get thread-local storage value (maybe per-thread state)
    TlsGetValue(g_TlsSlotEntityData);

    // Allocate a temporary object of size 0x70 with flags 0x27 (likely debug allocation)
    int* tempObj = (int*)customAllocate(0x70, 0x27);
    *(short*)(tempObj + 4) = 0x70; // Store allocation size at offset 4 for debugging

    // Get or create a reference-counted object from entity's data offset +0x10
    refCountedObj = (undefined4*)getOrCreateRefCountedObject(*(undefined4*)(entityId + 0x10), &g_EmptyString);

    // Register entity and collection with some management function (maybe add to list)
    registerEntityInCollection(entityId, collection, arg4, arg5, 0xffffffff);

    // Decrement reference count; if it reaches zero, call virtual destructor
    if (*(short*)(refCountedObj + 1) != 0) // refCountedObj[1] is short at offset 4? Actually +1 word = offset 4
    {
        *(short*)((int)refCountedObj + 6) = *(short*)((int)refCountedObj + 6) - 1; // offset 6: another count?
        if (*(short*)((int)refCountedObj + 6) == 0)
        {
            // Call virtual function at offset 0 (likely delete or release)
            (**(code**)(*refCountedObj))(1);
        }
    }

    // Access collection's internal array
    iVar1 = *(int*)(collection + 8);
    if (iVar1 == 0)
    {
        thisPtr->field_0x48 = 1;
        return;
    }

    if (*(int*)(iVar1 + 0x60) < 1) // Check if capacity is zero
    {
        thisPtr->field_0x48 = 1;
        return;
    }

    // Search collection's entity ID array for matching entityId
    iVar3 = 0;
    if (*(int*)(iVar1 + 0xc) > 0) // Number of entries
    {
        pEntityArray = *(int**)(iVar1 + 8); // Pointer to array of entity IDs
        do
        {
            if (*pEntityArray == entityId)
            {
                if (iVar3 < 0) goto END; // Negative index check
                if (iVar3 < *(int*)(iVar1 + 0x60))
                {
                    // Copy associated data from collection's data array into refCountedObj at offset 8
                    refCountedObj[2] = *(undefined4*)(*(int*)(iVar1 + 0x5c) + iVar3 * 4);
                    goto END;
                }
                break;
            }
            iVar3 = iVar3 + 1;
            pEntityArray = pEntityArray + 1;
        } while (iVar3 < *(int*)(iVar1 + 0xc));
    }

END:
    thisPtr->field_0x48 = 1;
    return;
}