// FUNC_NAME: HashTable::updateData
void HashTable::updateData(uint key, uint* data) {
    HashTable* table = *(HashTable**)(DAT_01223398 + 8); // global hash table pointer
    uint bucketIndex = key % table->bucketCount;
    HashNode* node = table->buckets[bucketIndex]; // linked list head

    // Search for existing node with matching key
    while (node != nullptr) {
        if (node->key == key) {
            if (node->value != nullptr) {
                uint* obj = node->value; // pointer to target object
                // Copy transform data (offsets 0x30-0x3c)
                *(Vector4*)(obj + 0x30) = *(Vector4*)(data + 4);  // data[4..7] -> obj[0x30..0x3c]
                // Copy second vector (offsets 0x70-0x7c)
                *(Vector4*)(obj + 0x70) = *(Vector4*)(data + 0);  // data[0..3] -> obj[0x70..0x7c]
                // Copy scalar fields
                obj[0x84] = data[10];  // data[10]
                obj[0x88] = data[8];   // data[8]
                obj[0x8c] = data[9];   // data[9]
                // Set dirty flag
                *(byte*)(obj + 0x98) = 1;
            }
            return;
        }
        node = node->next;
    }
    // If not found, do nothing (original code would crash if writing to null)
}