// FUNC_NAME: HashTable::LookupKeyValue
unsigned int HashTable::LookupKeyValue(unsigned int key)
{
    if (key == 0) {
        return 0;
    }

    // Global hash table: array of 4096 bucket pointers (each 4 bytes)
    // Base address stored at DAT_012058e0
    unsigned int* bucketPtr = reinterpret_cast<unsigned int*>(DAT_012058e0 + (key & 0xFFF) * 4);
    unsigned int bucketHead = *bucketPtr;
    if (bucketHead == 0) {
        return 0xFFFFFFFF; // sentinel for "not found"
    }

    // Traverse linked list nodes at offset +0x38 (nextPtr) and compare key at +0x34
    struct HashNode {
        unsigned int field_0x00; // unknown, not used here
        unsigned int value;      // +0x04: the stored value to return
        unsigned int field_0x08; // padding?
        // ... (other fields up to +0x34)
        unsigned int key;        // +0x34: the lookup key
        HashNode* next;          // +0x38: next node in chain
    };

    HashNode* currentNode = reinterpret_cast<HashNode*>(bucketHead);
    while (currentNode->key != key) {
        currentNode = currentNode->next;
        if (currentNode == nullptr) {
            return 0xFFFFFFFF;
        }
    }

    return currentNode->value; // +0x04
}