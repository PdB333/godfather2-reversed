// FUNC_NAME: EntityDataManager::createEntity
// Function address: 0x004f4e70
// Creates a new entity object, initializes it with given parameters, and inserts into global hash table keyed by entityKey.

void EntityDataManager::createEntity(uint entityKey, int param2, int param3, int param4, int param5, int param6, int param7)
{
    uint hashTableInfo[4]; // local_10, used for hash table insert parameters
    int *newObject; // puVar1

    hashTableInfo[1] = 2;      // +4: some flag/type
    hashTableInfo[2] = 0x10;   // +8: size or count
    hashTableInfo[3] = 0;      // +12: reserved

    // Allocate 44 bytes (0x2c) for the new entity object
    newObject = (int *)earsMemAlloc(0x2c, &hashTableInfo[1]);  // FUN_009c8ed0

    if (newObject != nullptr)
    {
        newObject[1] = param3;   // +0x04: entity field 3
        newObject[2] = param4;   // +0x08: entity field 4
        newObject[3] = param5;   // +0x0c: entity field 5
        newObject[5] = param2;   // +0x14: entity field 2 (offset 20)
        newObject[0] = (int)&entityVTable;  // +0x00: vtable pointer (PTR_FUN_00e37798)
        newObject[4] = 0;        // +0x10: reserved/initialized to 0
        newObject[6] = param6;   // +0x18: entity field 6
        newObject[7] = param7;   // +0x1c: entity field 7
        newObject[8] = 0;        // +0x20: reserved
        newObject[9] = 0;        // +0x24: reserved
        newObject[10] = 0;       // +0x28: reserved
    }

    // Prepare hash table insertion: key = entityKey, value = newObject
    hashTableInfo[0] = entityKey;   // key for lookup

    // Compute hash index: entityKey % (global hash table size)
    // DAT_01223398 is the global hash table structure; +8 is a pointer to capacity info
    uint hashIndex = entityKey % *(uint *)(*(int *)(gHashTable + 8) + 8);

    // Insert the new entity into the hash table
    hashTableInsert(hashTableInfo, &newObject, hashIndex);  // FUN_00423cf0
}