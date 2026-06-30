// FUNC_NAME: HashTable::findByPredicate
struct HashTableNode {
    void* data;       // +0x00
    void* unknown;    // +0x04 (not used in predicate)
    void* value;      // +0x08
    HashTableNode* next; // +0x0C
};

struct BucketArray {
    HashTableNode** buckets; // +0x00
    int             count;   // +0x04
};

// Returns index of found element or -1 if not found
int HashTable::findByPredicate(uint (__cdecl *predicate)(void* data, void* value, uint extra), uint extra)
{
    BucketArray* bucketInfo = *(BucketArray**)((char*)this + 0x30);
    uint bucketIndex = 0;
    int elementIndex = 0;

    lockTable(); // FUN_00573aa0

    HashTableNode* current = nullptr;

    // Start with first non-empty bucket
    do {
        // Iterate through buckets until one has a node
        while (bucketIndex < (uint)bucketInfo->count) {
            current = bucketInfo->buckets[bucketIndex];
            bucketIndex++;
            if (current != nullptr) break;
        }
        if (current == nullptr) break;

        // Iterate through linked list of this bucket
        for (; current != nullptr; current = current->next) {
            uint result = predicate(current->data, current->value, extra);
            if ((result & 1) != 0) {
                return elementIndex;
            }
            elementIndex++;
        }
    } while (current != nullptr);

    return -1;
}