// FUNC_NAME: HashArrayTable::removeEntry
// Function address: 0x006552f0
// Removes an element from both the linear array (for iteration) and the hash table (for lookup).
// The hash table uses open addressing with linear probing; on removal, subsequent entries are rehashed.

class HashArrayTable {
public:
    // Offsets from this (param_1):
    // +0x0: vtable? not used
    // +0xc: count of elements (int)
    // +0x14: pointer to array of element pointers (int**)
    // +0x18: hash table size (uint)
    // +0x20: pointer to hash bucket array (int**)

    // Element structure (param_2):
    // +0x0: vtable pointer
    // +0x8: reference count (int)
    // +0x102: ushort hash_part1
    // +0x104: int hash_part2
    // +0x108: int hash_part3
    // +0x10c: int hash_part4

    void removeEntry(int* element);
};

void HashArrayTable::removeEntry(int* element) {
    int count = *(int*)(this + 0xc);
    int* arrayBase = *(int**)(this + 0x14);
    int i;

    // Search linear array for element and remove it by swapping with last element
    if (count > 0) {
        for (i = 0; i < count; i++) {
            if (arrayBase[i] == element) {
                if (i != count - 1) {
                    // Move last element to this position
                    arrayBase[i] = arrayBase[count - 1];
                }
                // Decrement count
                *(int*)(this + 0xc) = count - 1;
                break;
            }
        }
    }

    // Compute original hash for element
    uint hashTableSize = *(uint*)(this + 0x18);
    uint originalHash = ((((uint)*(ushort*)((int)element + 0x102) ^ (uint)(element[0x42] << 8)) * 8 ^ (uint)element[0x43]) << 5) ^ ((uint)element[0x42] >> 0x10) ^ (uint)element[0x41];
    uint bucketIdx = originalHash % hashTableSize;

    int* hashTable = *(int**)(this + 0x20);

    // Find the element in the hash table (linear probing)
    uint idx = bucketIdx;
    while (true) {
        if (hashTable[idx] == element) {
            // Remove element from hash table
            hashTable[idx] = 0;

            // Rehash subsequent non-empty buckets to maintain probe sequence
            while (true) {
                idx = (idx + 1) % hashTableSize;
                int* nextElement = hashTable[idx];
                if (nextElement == 0) break;

                // Remove next element from its current bucket
                hashTable[idx] = 0;

                // Compute new hash for nextElement
                uint newHash = ((((uint)*(ushort*)((int)nextElement + 0x102) ^ (uint)(nextElement[0x42] << 8)) * 8 ^ (uint)nextElement[0x43]) << 5) ^ ((uint)nextElement[0x42] >> 0x10) ^ (uint)nextElement[0x41];
                uint newBucketIdx = newHash % hashTableSize;

                // Find next empty bucket starting from newHash
                int* table = *(int**)(this + 0x20);
                uint probeIdx = newBucketIdx;
                while (table[probeIdx] != 0) {
                    probeIdx = (probeIdx + 1) % hashTableSize;
                }
                table[probeIdx] = nextElement;
            }

            // Decrement reference count on element
            int* refCount = element + 2; // +8 bytes from element
            *refCount = *refCount - 1;
            if (*refCount == 0) {
                // Call virtual destructor via vtable+8
                (**(code**)(*element + 8))(); // vtable[2] is the destructor
            }
            return;
        }

        idx = (idx + 1) % hashTableSize;
        if (idx == originalHash) break; // wrapped around, element not found
    }
}