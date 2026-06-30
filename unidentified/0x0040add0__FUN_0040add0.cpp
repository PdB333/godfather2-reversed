extern "C" unsigned int __thiscall FUN_0040add0(void* this_, unsigned int key)
{
    struct HashNode
    {
        unsigned int key;    // 0x00
        unsigned int value;  // 0x04
        HashNode* next;      // 0x08
    };

    struct HashTable
    {
        void* field_00;           // 0x00
        HashNode** buckets;       // 0x04
        unsigned int bucketCount; // 0x08
    };

    auto* self = static_cast<HashTable*>(this_);

    HashNode* node = self->buckets[key % self->bucketCount];

    while (true) {
        if (node == nullptr) {
            return 0;
        }

        if (node->key == key) {
            break;
        }

        node = node->next;
    }

    if (node == nullptr) {
        return 0;
    }

    if (reinterpret_cast<unsigned int*>(node) + 1 == nullptr) {
        return 0;
    }

    return node->value;
}