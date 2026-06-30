// FUNC_NAME: EventManager::addEvent
void EventManager::addEvent(uint eventId, uint data0, uint data1, uint data2, uint data3)
{
    uint allocParams[4]; // alignment/flags for allocator
    allocParams[1] = 2; // allocation flags?
    allocParams[2] = 0x10; // alignment?
    allocParams[3] = 0; // reserved

    EventNode *node = (EventNode *)MemoryAlloc(0x40, allocParams + 1); // size 64 bytes
    uint someGlobal = g_globalFlags; // DAT_00e2b1a4, likely a global singleton or flag

    if (node != nullptr)
    {
        // Initialize node fields
        node->vtable = &s_EventNodeVTable; // PTR_LAB_00e3738c
        node->field_0x04 = data1;
        node->field_0x08 = data2;
        node->field_0x0C = data3;
        node->field_0x30 = someGlobal;
        node->field_0x24 = data0;
        node->field_0x28 = 0;
        node->field_0x2C = 0xFFFFFFFF; // invalid index
        node->field_0x34 = 0;
        node->field_0x38 = 0;
        node->field_0x1C = 0;
        node->field_0x18 = 0;
        node->field_0x14 = 0;
        node->field_0x10 = 0;
        node->field_0x20 = 0;
    }

    // Insert into hash table
    allocParams[0] = eventId; // key
    uint hashIndex = eventId % g_pHashTable->hashSize; // DAT_01223398 + 8 -> hash table size
    HashTableInsert((HashKey *)allocParams, &node, hashIndex); // FUN_00423cf0
}