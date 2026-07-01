// FUNC_NAME: HashTable::validateEntryNotInAnyBucket
// Address: 0x00785bd0
// This function iterates over all buckets in a hash table and checks that the node
// embedded at offset 0x20 of the given entry is not already present in any list.
// If a duplicate is found, it calls an error handler (FUN_00788320) and returns.
// Offsets:
// this+0x1a3c: uint m_bucketCount
// this+0x193c: Bucket** m_buckets (array of pointers to Bucket)
// Bucket structure: sentinel node starts at offset 0x008
// Node structure: pNext at +0x000, pPrev at +0x004 (not used here)
// Entry structure: Node m_node at +0x020

struct Node {
    Node* pNext;
    Node* pPrev;
};

struct Bucket {
    // unknown padding
    Node sentinel; // offset 0x008
};

struct Entry {
    // ... (unknown fields)
    Node m_node; // offset 0x020
};

// Forward declaration of error handler
void assertOrBreak(void);

void __thiscall HashTable::validateEntryNotInAnyBucket(Entry* pEntry) {
    if (m_bucketCount == 0) {
        return;
    }

    Bucket** buckets = reinterpret_cast<Bucket**>(m_buckets); // offset 0x193c
    for (uint i = 0; i < m_bucketCount; i++) {
        Bucket* bucket = buckets[i];
        Node* sentinel = &bucket->sentinel;        // bucket + 0x008
        Node* current = sentinel->pNext;           // first real node or sentinel itself if empty

        while (current != sentinel) {
            // Compute address of the node inside pEntry (offset 0x20)
            Node* entryNode = nullptr;
            if (pEntry != nullptr) {
                entryNode = reinterpret_cast<Node*>(
                    reinterpret_cast<char*>(pEntry) + 0x20
                );
            }

            if (current == entryNode) {
                assertOrBreak(); // FUN_00788320
                return;
            }

            current = current->pNext; // move to next node
        }
    }
}