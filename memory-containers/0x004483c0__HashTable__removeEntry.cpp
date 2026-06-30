// FUNC_NAME: HashTable::removeEntry

// Reconstructed C++ for function at 0x004483c0
// This function removes an entry from a two-level hash table.
// First level: hash table keyed by a 128-bit primary key (obtained via getCurrentPrimaryKey).
// Second level: within each primary key group, a doubly-linked list of entries keyed by secondaryKey (param_2).
// Offsets:
// +0x70: pointer to bucket array (array of pointers to HashEntry)
// +0x74: number of buckets
// HashEntry layout:
//   +0x00: primary key (4 x uint32_t)
//   +0x08: secondary key (int32_t)
//   +0x0c: pointer to previous entry in secondary list (or 0 if first)
//   +0x10: pointer to next entry in secondary list (or 0 if last)
//   +0x18: pointer to next entry in primary collision chain (or 0 if end)
// getCurrentPrimaryKey() returns a pointer to the 128-bit key used for lookups.
// hashPrimaryKey() computes the bucket index from the key.

// Forward declarations for helper functions
uint32_t* getCurrentPrimaryKey();                          // FUN_0043ab10
uint32_t hashPrimaryKey(uint32_t* key);                    // FUN_004209c0
void onPrimaryGroupHeadRemoved();                          // FUN_00448760
void updateBucketPointerForNewHead();                      // FUN_00448a40

void HashTable::removeEntry(int32_t secondaryKey)
{
    uint32_t* primaryKey = getCurrentPrimaryKey();
    uint32_t bucketIndex = hashPrimaryKey(primaryKey) % this->bucketCount;
    HashEntry* entry = this->bucketArray[bucketIndex];

    // Walk the primary collision chain to find the group with matching primary key
    while (entry != nullptr)
    {
        uint32_t* nodeKey = getCurrentPrimaryKey(); // Get primary key of this node
        if (nodeKey[0] == primaryKey[0] &&
            nodeKey[1] == primaryKey[1] &&
            nodeKey[2] == primaryKey[2] &&
            nodeKey[3] == primaryKey[3])
        {
            break; // Found the correct primary key group
        }
        entry = entry->nextPrimary; // Offset +0x18
    }

    if (entry == nullptr)
        return; // No group with this primary key

    HashEntry* node = entry;
    // Search within the secondary list for the given secondaryKey
    while (node != nullptr && node->secondaryKey != secondaryKey)
    {
        node = node->nextSecondary; // Offset +0x10
    }

    if (node == nullptr)
        return; // No entry with this secondary key

    // Remove node from secondary doubly linked list
    if (node->prevSecondary != nullptr)
    {
        node->prevSecondary->nextSecondary = node->nextSecondary;
    }
    if (node->nextSecondary != nullptr)
    {
        node->nextSecondary->prevSecondary = node->prevSecondary;
    }

    // If the removed node was the head of this primary group
    if (node == entry)
    {
        onPrimaryGroupHeadRemoved();
        // If there is a next entry in the secondary list, update the bucket pointer
        if (node->nextSecondary != nullptr)
        {
            updateBucketPointerForNewHead();
        }
    }
}