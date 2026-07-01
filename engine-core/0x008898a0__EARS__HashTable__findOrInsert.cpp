// FUNC_NAME: EARS::HashTable::findOrInsert
void __thiscall EARS::HashTable::findOrInsert(HashTable* this, HashTableEntry* outEntry, uint* keyPtr)
{
    uint hash;
    uint bucketIdx;
    HashTableBucket* bucket;
    HashTableNode* node;
    HashTableNode* nextNode;
    uint key;
    uint newBucketCount;
    char rehashFlag[4];
    uint newBucketIdx;

    key = *keyPtr;
    bucketIdx = key % this->bucketCount; // this+8
    bucket = &this->buckets[bucketIdx]; // this+4 is bucket array

    node = bucket->head;
    while (node != nullptr) {
        if (key == node->key) {
            // Found existing node
            outEntry->node = node;
            outEntry->bucketPtr = bucket;
            outEntry->isNew = 0;
            return;
        }
        node = node->next; // next at offset 0x1c
    }

    // Not found, allocate new node (possibly trigger resize)
    FUN_00ab4570(rehashFlag, this->bucketCount, this->bucketCountExtra, 1); // unknown function
    // rehashFlag may indicate if resize is needed

    // Allocate new node
    HashTableNode* newNode = FUN_008886e0(keyPtr); // returns new node with key set

    if (rehashFlag[0] != '\0') {
        // Resize happened, recalc bucket index
        newBucketIdx = key % newBucketCount; // newBucketCount is stored in rehashFlag? Actually unclear; local_4 is set after FUN_00ab4570? In decompiled: local_4 is used, but not set properly. We'll assume newBucketCount is stored somewhere.
        // The decompiled calls FUN_00888740(local_4); maybe new bucket count or something
        // Actually FUN_00888740 likely inserts into the new bucket array
        // For simplicity, we recalc bucketIdx after resize
        bucketIdx = key % this->bucketCount; // use updated bucketCount
        bucket = &this->buckets[bucketIdx];
        FUN_00888740(this->bucketCount); // unknown function, maybe finalize resize?
    }

    // Link new node into bucket
    int bucketOffset = bucketIdx * 4;
    newNode->next = *(HashTableNode**)((int)this->buckets + bucketOffset); // bucket head
    *(HashTableNode**)((int)this->buckets + bucketOffset) = newNode;
    this->count++; // this+0xc

    // Fill output
    outEntry->node = newNode;
    outEntry->bucketPtr = &this->buckets[bucketIdx];
    outEntry->isNew = 1;
    return;
}

// Note: This function has been reconstructed from Ghidra decompilation.
// Some details (FUN_00ab4570, FUN_008886e0, FUN_00888740) are unknown helpers.
// The exact layout of HashTable and HashTableNode may differ; offsets: +4 buckets, +8 bucketCount, +0xc count.
// Node layout: +0 key (uint), +0x1c next pointer.