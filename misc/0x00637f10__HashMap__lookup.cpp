// FUNC_NAME: HashMap::lookup
// Function at 0x00637f10: Lookup entry by integer key in a hybrid direct/hash map.
// Structure (this at ESI):
//   +0x07: hashTableSizeShift (byte) - determines hash table size: (1 << (shift & 0x1f)) - 1 | 1
//   +0x0c: directArray (int*) - array of 8-byte entries for keys 1..directCount
//   +0x10: hashTable (int*) - array of hash bucket heads (each bucket is a linked list node of 20 bytes)
//   +0x1c: directCount (int) - number of direct entries (max key for direct lookup)
// Hash node layout (20 bytes):
//   +0x00: tag (int) - must be 3 for valid node
//   +0x04: key (float) - the key as float
//   +0x08: data (int[2]) - the returned data pointer points here (node+2)
//   +0x10: next (int*) - pointer to next node in chain
// Sentinel global: DAT_00e2a93c (null entry pointer)

int* HashMap::lookup(int key) {
    // Direct lookup for small positive keys
    if (key > 0 && key <= this->directCount) {
        // Return pointer to the key-th entry in directArray (each entry is 8 bytes)
        return (int*)(this->directArray + (key - 1) * 2); // 2 ints per entry
    }

    // Hash table lookup for larger keys
    // Compute hash index: (key + hashSeed) % hashTableSize
    // hashTableSize = (1 << (hashTableSizeShift & 0x1f)) - 1 | 1
    unsigned int hashTableSize = (1 << (this->hashTableSizeShift & 0x1f)) - 1 | 1;
    unsigned int hashIndex = (unsigned int)((float)key + DAT_00e2b1a4) % hashTableSize;

    // Traverse the chain at this bucket
    int* node = (int*)(this->hashTable + hashIndex * 5); // 5 ints per node (20 bytes)
    while (true) {
        if (node[0] == 3 && *(float*)&node[1] == (float)key) {
            // Found: return pointer to data (skip tag and key)
            return node + 2;
        }
        node = (int*)node[4]; // next pointer
        if (node == nullptr) {
            break;
        }
    }
    // Not found: return sentinel
    return &DAT_00e2a93c;
}