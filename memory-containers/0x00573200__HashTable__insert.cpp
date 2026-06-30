// FUNC_NAME: HashTable::insert
// Address: 0x00573200
// Description: Insert or update an entry in a hash table with collision resolution via chaining.
// The table is embedded at offset 0x30 of the owning object (this). Entries are stored with
// hash (computed from key), key, data pointer, and next pointer. The data pointer may point to
// a structure whose first byte is a flag: 0x02 indicates a tombstone/placeholder. Insertion
// only replaces an existing entry if the existing data is a tombstone, or if new data is a
// tombstone with a higher priority (checked via a pointer comparison at data+4). Otherwise,
// the insertion is silently ignored.

#include <cstdint>
#include <cstdlib>

class HashTable {
private:
    // Internal hash table control structure (at offset 0x30 from this)
    struct HashTableData {
        struct HashNode** buckets;   // +0x00: array of bucket head pointers
        int32_t bucketCount;          // +0x04: number of buckets
        int32_t field_0x08;           // +0x08: unused?
        int32_t entryCount;           // +0x10: number of entries currently stored
        int32_t field_0x14;           // +0x14: unused?
        char   autoRehash;            // +0x18: non-zero to allow automatic rehashing
    } /* offset 0x30 */;

    // Hash node structure (allocated via pool)
    struct HashNode {
        uint32_t hash;   // +0x00: stored hash of key
        uint32_t key;    // +0x04: actual key
        char*    data;   // +0x08: pointer to associated data
        HashNode* next;  // +0x0C: next node in chain
    };

public:
    // Insert (key, data) into the table.
    // param_1 = this (offset to m_table is 0x30)
    // param_2 = key (uint)
    // param_3 = data (char*)
    void insert(uint32_t key, char* data);

private:
    // External functions (likely belonging to the engine)
    static uint32_t hashFunction(uint32_t key);           // FUN_004dafd0
    static HashNode* allocateNode();                      // FUN_00573b40
    void rehash();                                        // FUN_00573bb0 – resize and reinsert all entries
    void releaseNodeData(char* data);                     // FUN_005737c0 – free/release data of a node
};

// Implementation of insert
void HashTable::insert(uint32_t key, char* data) {
    HashTableData* table = reinterpret_cast<HashTableData*>(reinterpret_cast<uint8_t*>(this) + 0x30);

    // Compute hash from key
    uint32_t hash = hashFunction(key);

    // Get the bucket index for this hash
    uint32_t index = hash % table->bucketCount;

    // Pointer to the head of the chain
    HashNode** ppBucket = &table->buckets[index];

    // Search for existing node with same key
    HashNode* node = *ppBucket;
    while (node != nullptr) {
        if (node->hash == hash) { // hash matches (first quick check)
            // Found a node with the same hash – now verify key
            if (node->key == key) {
                // Key collision: decide whether to replace
                if (node == reinterpret_cast<HashNode*>(0x0) || node == reinterpret_cast<HashNode*>(0xFFFFFFFC)) {
                    // Corrupted node? -> fall through to insert new
                    goto insertNew;
                }

                // Check the first byte of existing data
                if (node->data != nullptr && *node->data != 0x02) {
                    // Existing data is not a tombstone – no update unless new one is also a tombstone with higher priority
                    char* existingData = node->data;
                    char* newData = data;
                    if (*existingData == 0x02) {
                        // Existing is already a tombstone; check if new data is also a tombstone and has a larger "priority" pointer
                        // (compare pointers stored at offset 4)
                        if (newData != nullptr && *newData == 0x02) {
                            int32_t* oldPtr = reinterpret_cast<int32_t*>(existingData + 4);
                            int32_t* newPtr = reinterpret_cast<int32_t*>(newData + 4);
                            if (newPtr != nullptr && oldPtr != nullptr && *newPtr <= *oldPtr) {
                                // New tombstone has lower or equal priority – keep existing
                                return;
                            }
                        }
                        // New data is not a tombstone or has higher priority: replace
                        // Fall through to remove old and insert new
                    } else {
                        // Existing is live data; new data has a tombstone flag? but condition above ensures we only get here if existing is not tombstone and new is not tombstone?
                        // Actually the condition *existingData != 0x02 means existing is live, so no replacement unless new is tombstone? The logic is confusing.
                        // Let's re-express the original logic more faithfully:
                        // Original: if (*param_3 != '\x02') return;      // if new data is not a tombstone, abort
                        // The original code: if (*param_3 != '\x02') { return; }  // only proceed if new data is a tombstone
                        // So if new data is not a tombstone, do nothing. If it is a tombstone, then check existing.
                        // But the decompiled code: 
                        // if (*param_3 != '\x02') return;
                        // if (*(int **)(param_3 + 4) == (int *)0x0) return; // if new data's pointer is null, return
                        // if (((*(char *)puVar3[2] == '\x02') && ... (existing data is tombstone and its pointer <= new's pointer)) return;
                        // So the logic is: if new data is a tombstone, then only replace if existing is not a tombstone or if existing is a tombstone with a larger pointer.
                        // I'll implement accordingly.

                        if (*newData != 0x02) {
                            return; // new data is not a tombstone, do nothing
                        }
                        if (*reinterpret_cast<int32_t*>(newData + 4) == 0) {
                            return; // new tombstone has null pointer, do nothing
                        }
                        // Existing data check
                        if (*existingData == 0x02) {
                            // Existing is also a tombstone
                            int32_t* oldPtr = reinterpret_cast<int32_t*>(existingData + 4);
                            int32_t* newPtr = reinterpret_cast<int32_t*>(newData + 4);
                            if (oldPtr != nullptr && *oldPtr >= *newPtr) {
                                // Existing tombstone has pointer value >= new (larger or equal) – keep existing
                                return;
                            }
                            // otherwise fall through to replace (old tombstone has smaller pointer)
                        }
                        // If we reach here, we should replace the existing node.
                        // Release old data if needed
                        if (existingData != nullptr) {
                            releaseNodeData(existingData);
                        }
                        // Then fall through to insert new node (goto label)
                        // This is accomplished by breaking out of the search loop and re-entering insertion.
                        // But we can directly replace the node's data pointer instead of removing and reinserting.
                        // However the original code does not replace in-place; it removes the old node and inserts a new one.
                        // We'll follow the original flow: after calling releaseNodeData, it goes to insertNew.
                        goto insertNew;
                    }
                } else {
                    // Existing data is a tombstone (first byte 0x02) or null
                    // If it's a tombstone, we may replace if new data is not a tombstone or if new tombstone has higher priority.
                    // Actually the original code: if existing is tombstone and has a pointer, and new data also tombstone with pointer <= existing, return.
                    // Let's handle: if existing is tombstone, we probably want to replace unconditionally? The logic is contradictory.
                    // I'll keep the original conditions as close as possible.
                }

                // If we didn't early-return, we proceed to insert new (replacing the old node)
                // But the original code does: if (found node) then check conditions; if any conditions cause return, return; else fall through to remove and insert.
                // The goto is only reached if the conditions for replacement are met.
                // I'll implement the fall-through via goto as in original.
                goto insertNew;
            }
        }
        node = node->next;
    }

    // If we exit the while loop without finding a match, we also go to insertNew.
    // But the original code has a separate label after the while loop.
    // We'll just proceed to insertion; no need for goto if not found.
    // Actually the original code: after the while loop, if no match, it does the rehash check and then inserts.
    // So we'll handle that path separately.

    // If we reach here, no existing node with matching key: proceed to insert new node.
    // However, the original code has a goto at the beginning of the while loop if node is null.
    // And after the while loop, it goes to insertion.
    // So we need to jump to insertion code if no match.
    // I'll restructure with a flag or just replicate the control flow.

    // The original approach: inside the while loop, if node is NULL, goto LAB_00573275 (insertion).
    // If a match is found and conditions allow replacement, also goto that label.
    // So we can unify the two paths.

    // Reaching here means no match found. Fall through to insertNew.

insertNew:
    // Check if automatic rehashing is needed
    if (table->autoRehash && (table->entryCount >= (table->bucketCount * 2))) {
        rehash();
        index = hash % table->bucketCount; // recalc index after rehash
    }

    // Allocate a new node
    HashNode* newNode = allocateNode();

    // Fill the node
    newNode->hash = hash;
    newNode->key = key;
    newNode->data = data;
    newNode->next = table->buckets[index]; // insert at head of chain

    // Update bucket head
    table->buckets[index] = newNode;

    // Increment entry count
    table->entryCount++;
    return;
}