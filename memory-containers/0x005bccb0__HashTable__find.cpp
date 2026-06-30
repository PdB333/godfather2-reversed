// FUNC_NAME: HashTable::find
uint HashTable::find(uint *keyPtr) {
    uint key = *keyPtr;
    // Static initialization of the hash table singleton
    if ((s_initialized & 1) == 0) {
        s_initialized |= 1;
        s_vtable = &g_vtable; // +0x0: vtable pointer
        FUN_004cfc30(0x200);  // Allocate 0x200 bytes for the table
        atexit(cleanupFunc);  // Register cleanup on exit
    }
    // Compute bucket index using modulo of table size
    uint bucketIndex = key % s_tableSize; // s_tableSize at DAT_01225e18
    HashNode *node = s_table[bucketIndex]; // s_table at DAT_01225e14
    while (node != nullptr) {
        if (node->key == key) {
            return node->value; // node[1] is the value
        }
        node = node->next; // node[2] is the next pointer
    }
    return 0; // Not found
}