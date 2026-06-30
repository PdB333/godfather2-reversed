// FUNC_NAME: HashTableManager::insertNewNode
void HashTableManager::insertNewNode(unsigned int id, void* owner, int arg3, int arg4, int arg5) {
    // Allocate 40-byte node with alignment flags 2, 0x10, 0
    uint allocFlags[] = {2, 0x10, 0};
    HashNode* node = (HashNode*)allocateMemory(0x28, allocFlags + 1);
    if (node == nullptr) {
        node = nullptr;
    } else {
        // Initialize node fields
        node->field_04 = arg3;        // +0x04
        node->field_0C = arg5;        // +0x0C
        node->field_08 = arg4;        // +0x08
        node->field_14 = 0;           // +0x14
        node->field_18 = 0;           // +0x18
        node->vtable = &vtableSymbol; // +0x00 set to class vtable
        node->field_10 = owner;       // +0x10
        node->field_1C = globalCounter; // +0x1C from global DAT_00e2b1a4
        node->field_20 = *(int*)((char*)owner + 0x20); // +0x20 read from owner's field at +0x20
    }

    // Compute hash bucket index from ID
    uint bucketIndex = id % *(uint*)(*(int*)(hashTableGlobal + 8) + 8);
    uint keyArray[] = {id};
    HashNode* nodePtr = node;
    insertIntoHashTable(keyArray, &nodePtr, bucketIndex); // insert node into hash table
}