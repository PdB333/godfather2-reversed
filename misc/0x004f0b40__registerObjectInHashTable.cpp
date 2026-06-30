// FUNC_NAME: registerObjectInHashTable
void registerObjectInHashTable(uint key, uint arg2, uint arg3, uint arg4, uint arg5, uint arg6, uint arg7)
{
    // Local array used as input to the hash table insertion function.
    // [0] = key, [1] = 2 (maybe flags?), [2] = 0x10 (maybe bucket count?), [3] = 0 (unused?)
    uint localArray[4];
    localArray[1] = 2;
    localArray[2] = 0x10;
    localArray[3] = 0;

    // Allocate a new object of size 0x1C (28 bytes) with alignment/flags from localArray+1.
    // The allocation function at 0x009c8ed0 takes size and a pointer to a struct with flags.
    HashNode* newNode = (HashNode*)Allocate(0x1C, &localArray[1]);
    if (newNode != nullptr)
    {
        // Set the vtable pointer (class-specific).
        newNode->vtable = &PTR_LAB_00e37438; // +0x00
        // Store the constructor arguments into the node.
        newNode->field1 = arg2;   // +0x04
        newNode->field2 = arg6;   // +0x08
        newNode->field3 = arg7;   // +0x0C
        newNode->field4 = arg3;   // +0x10
        newNode->field5 = arg4;   // +0x14
        newNode->field6 = arg5;   // +0x18
    }

    // Compute hash bucket index from the key modulo hash table size.
    // DAT_01223398 is a pointer to the hash table manager.
    // At offset +0x08 is a pointer to the bucket array, and at offset +0x08 of that is the bucket count.
    uint bucketCount = *(uint*)(*(int*)(DAT_01223398 + 8) + 8);
    uint bucketIndex = key % bucketCount;

    // Insert the key and the new node into the hash table.
    localArray[0] = key;
    HashTableInsert(localArray, &newNode, bucketIndex);
}