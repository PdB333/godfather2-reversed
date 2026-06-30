// FUNC_NAME: EntityManager::setEntityComponentData
void EntityManager::setEntityComponentData(uint entityId, uint* componentData)
{
    // Get global hash table manager structure
    // DAT_01223398 is a global pointer to the hash table manager
    HashTableManager* hashTableMgr = *(HashTableManager**)(DAT_01223398 + 8); // +0x8: pointer to manager
    uint bucketCount = *(uint*)(hashTableMgr + 8); // +0x8: number of buckets
    uint bucketIndex = entityId % bucketCount;
    uint** bucketArray = *(uint***)(hashTableMgr + 4); // +0x4: pointer to bucket array
    uint* entry = bucketArray[bucketIndex];

    while (entry != nullptr)
    {
        if (entry[0] == entityId)
        {
            // Found existing entry, get pointer to the component structure
            uint* componentStruct = (uint*)entry[1];
            if (componentStruct != nullptr)
            {
                // Copy component data into the structure at offsets 0x30 and 0x70
                // componentData layout: [0..3] -> offset 0x70, [4..7] -> offset 0x30
                componentStruct[0x70/4] = componentData[0];
                componentStruct[0x74/4] = componentData[1];
                componentStruct[0x78/4] = componentData[2];
                componentStruct[0x7C/4] = componentData[3];

                componentStruct[0x30/4] = componentData[4];
                componentStruct[0x34/4] = componentData[5];
                componentStruct[0x38/4] = componentData[6];
                componentStruct[0x3C/4] = componentData[7];

                // Copy additional fields
                componentStruct[0x8C/4] = componentData[8];
                componentStruct[0x84/4] = componentData[9];

                // Mark as initialized
                *(byte*)(componentStruct + 0x98/4) = 1;
            }
            return;
        }
        entry = (uint*)entry[2]; // next pointer
    }

    // Entry not found; nothing to update (no insertion)
    return;
}