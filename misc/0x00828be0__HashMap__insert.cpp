// FUNC_NAME: HashMap::insert
// Address: 0x00828be0
// Role: Inserts a key-value pair into a hash table, or returns existing node if key already present.
// The hash table uses chaining with linked lists. Bucket count at +0x8, bucket array at +0x4, element count at +0xC.
// Node structure: [key (4 bytes), value (4 bytes), next (4 bytes)]

struct HashMapNode {
    uint32_t key;
    uint32_t value;
    HashMapNode* next;
};

struct InsertResult {
    HashMapNode* node;      // pointer to the node (existing or new)
    uint8_t inserted;       // 0 if found, 1 if newly inserted
    HashMapNode** bucket;   // pointer to the bucket head pointer
};

void __thiscall HashMap::insert(uint32_t key, uint32_t value, InsertResult& result) {
    uint32_t bucketCount = *(uint32_t*)(this + 8);
    uint32_t bucketIndex = key % bucketCount;
    HashMapNode** bucketArray = *(HashMapNode***)(this + 4);
    HashMapNode* current = bucketArray[bucketIndex];

    // Walk the chain to find existing key
    while (current != nullptr) {
        if (current->key == key) {
            // Key found
            result.node = current;
            result.inserted = 0;
            result.bucket = &bucketArray[bucketIndex];
            return;
        }
        current = current->next;
    }

    // Key not found, need to insert
    // Check if rehash is needed
    bool needRehash;
    uint32_t newBucketCount;
    // FUN_00ab4570 checks load factor and returns new bucket count if rehash needed
    // It sets needRehash via first argument (bool pointer) and returns new size in eax
    // The decompiler shows local_8 and local_4; we simulate with a helper
    CheckRehash(needRehash, newBucketCount, bucketCount, *(uint32_t*)(this + 0xC));

    if (needRehash) {
        bucketIndex = key % newBucketCount;
        Rehash(newBucketCount); // FUN_00828940 - rehashes the table
        bucketArray = *(HashMapNode***)(this + 4); // bucket array may have changed
    }

    // Allocate new node
    HashMapNode* newNode = (HashMapNode*)AllocateNode(12, "EASTL", 0, 0,
        "c:\\packages001_pc\\EASTL\\1.09.02\\include\\EASTL/allocator.h", 0xE9);
    if (newNode != nullptr) {
        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;
    }

    // Insert at head of bucket
    newNode->next = bucketArray[bucketIndex];
    bucketArray[bucketIndex] = newNode;
    *(uint32_t*)(this + 0xC) += 1; // increment element count

    result.node = newNode;
    result.inserted = 1;
    result.bucket = &bucketArray[bucketIndex];
}