// FUNC_NAME: HashTable::resize
void __thiscall HashTable::resize(HashTable* this)
{
    uint newBucketCount = this->numBuckets * 2 + 1;
    Node** newBuckets = (Node**)malloc(newBucketCount * 4);
    memset(newBuckets, 0, newBucketCount * 4);

    uint bucketIndex = 0;
    if (this->numBuckets != 0) {
        do {
            Node* node = this->buckets[bucketIndex];
            while (node != nullptr) {
                void* data = node->data;
                // Key is 16 bytes at offsets 0x10-0x1f of the data
                uint32 keyParts[4];
                keyParts[0] = *(uint32*)((uint8*)data + 0x10);
                keyParts[1] = *(uint32*)((uint8*)data + 0x14);
                keyParts[2] = *(uint32*)((uint8*)data + 0x18);
                keyParts[3] = *(uint32*)((uint8*)data + 0x1c);

                Node* nextNode = node->next;
                HashInit(); // Possibly resets hash state
                uint hash = HashFunction(keyParts, 16);
                uint newIndex = hash % newBucketCount;
                node->next = newBuckets[newIndex];
                newBuckets[newIndex] = node;
                node = nextNode;
            }
            bucketIndex++;
        } while (bucketIndex < (uint)this->numBuckets);
    }

    free(this->buckets);
    this->buckets = newBuckets;
    this->numBuckets = newBucketCount;
}