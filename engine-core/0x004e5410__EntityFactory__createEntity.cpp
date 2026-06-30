// FUNC_NAME: EntityFactory::createEntity

void EntityFactory::createEntity(uint entityId, int param2, int param3, void* nodeData, int param5, int param6, int param7, int param8, int param9, int param10)
{
    int allocFlags[4]; // local_18, but only indices 1-3 used for allocation
    allocFlags[1] = 2;   // alignment or type
    allocFlags[2] = 0x10; // size? or flags
    allocFlags[3] = 0;    // zero

    // Allocate 0xA0 bytes for the entity object
    int* newEntity = (int*)FUN_009c8ed0(0xA0, &allocFlags[1]);
    if (newEntity != 0)
    {
        // Call the actual constructor with the remaining parameters
        newEntity = (int*)FUN_004e4e50(param2, param5, param6, param7, param8, param9, param10);
    }
    else
    {
        newEntity = 0;
    }

    // Prepare key array for hash table insertion
    int keyArray[5]; // local_18
    keyArray[0] = entityId;
    int entityPtr = (int)newEntity;

    // Compute hash bucket index
    int hashTableSize = *(int*)(*(int*)(DAT_01223398 + 8) + 8);
    int bucket = entityId % hashTableSize;

    // Insert into hash table (key = entityId, value = entity pointer)
    FUN_00423cf0(keyArray, &entityPtr, bucket);

    // If nodeData is provided, insert the entity into a linked list
    if (nodeData != 0)
    {
        int* node = (int*)FUN_0040add0(nodeData);
        int* listHeadPtr = (int*)(newEntity + 0x90); // +0x90: pointer to list head

        if (node == 0)
        {
            node = 0; // already zero
        }
        else
        {
            node = (int*)((int)node + 4); // skip some header? Actually +4 to get next pointer
        }

        if (*listHeadPtr != (int)node)
        {
            if (*listHeadPtr != 0)
            {
                FUN_004daf90(listHeadPtr); // remove old head
            }
            *listHeadPtr = (int)node;
            if (node != 0)
            {
                *(int*)(newEntity + 0x94) = *(int*)((int)node + 4); // +0x94: store next pointer
                *(int**)((int)node + 4) = listHeadPtr; // node->next = &listHeadPtr
            }
        }
    }
    return;
}