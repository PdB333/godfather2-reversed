// FUNC_NAME: DataHashMap::updateEntry
// Function at 0x0050ed10: Updates data associated with a key in a hash map.
// Assumes the key exists (no insertion logic). If not found, writes to null pointer (likely a bug or missing condition).
void DataHashMap::updateEntry(unsigned int key, const unsigned int* data) {
    // Access the BucketManager from global state.
    // Global structure: *(int *)(DAT_01223398 + 8) -> pointer to BucketManager
    struct BucketManager {
        unsigned int** buckets; // +0x04: array of pointers to linked list heads
        unsigned int bucketCount; // +0x08: number of buckets
    }* manager = *(BucketManager**)(DAT_01223398 + 8);

    unsigned int bucketIndex = key % manager->bucketCount;
    unsigned int* node = manager->buckets[bucketIndex]; // each node: [0] key, [1] data pointer, [2] next

    // Traverse the linked list
    while (node) {
        if (node[0] == key) {
            // Found node: node[1] is pointer to the data block
            unsigned int* dataBlock = (unsigned int*)node[1];
            if (node != nullptr && node + 1 != nullptr) { // sanity check (redundant in practice)
                // Copy 11 dwords (44 bytes) from input data to dataBlock at offset 0x20
                dataBlock[0x20/4] = data[0];  // offset 0x20
                dataBlock[0x24/4] = data[1];  // offset 0x24
                dataBlock[0x28/4] = data[2];  // offset 0x28
                dataBlock[0x2c/4] = data[3];  // offset 0x2c
                dataBlock[0x30/4] = data[4];  // offset 0x30
                dataBlock[0x34/4] = data[5];  // offset 0x34
                dataBlock[0x38/4] = data[6];  // offset 0x38
                dataBlock[0x3c/4] = data[7];  // offset 0x3c
                dataBlock[0x40/4] = data[8];  // offset 0x40
                dataBlock[0x48/4] = data[9];  // offset 0x48 (note: gap at 0x44)
                dataBlock[0x4c/4] = data[10]; // offset 0x4c
                return;
            }
            // Fall through to null case if sanity check fails (should not happen)
        }
        node = (unsigned int*)node[2]; // advance to next node
    }

    // Key not found: write to address 0x20 (null pointer dereference) – possibly a bug in original code.
    // Preserved for fidelity.
    unsigned int* nullBlock = nullptr;
    nullBlock[0x20/4] = data[0];
    nullBlock[0x24/4] = data[1];
    nullBlock[0x28/4] = data[2];
    nullBlock[0x2c/4] = data[3];
    nullBlock[0x30/4] = data[4];
    nullBlock[0x34/4] = data[5];
    nullBlock[0x38/4] = data[6];
    nullBlock[0x3c/4] = data[7];
    nullBlock[0x40/4] = data[8];
    nullBlock[0x48/4] = data[9];
    nullBlock[0x4c/4] = data[10];
}