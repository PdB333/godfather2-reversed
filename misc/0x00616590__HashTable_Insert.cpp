// FUNC_NAME: HashTable_Insert
// Address: 0x00616590
// Role: Insert a node into a hash table keyed by param_1 (hash index = param_1 & 0x1FF)
// Global hash table at DAT_01205968 with 512 buckets and a count at offset 0x800.
// Node structure (0xC bytes): +0 unknown (set to 0), +4 key, +8 next pointer.

struct HashNode {
    int field0;        // +0x00
    uint32_t key;      // +0x04
    HashNode* next;    // +0x08
};

struct GlobalHashTable {
    HashNode* buckets[512]; // +0x0000 to +0x07FF
    int count;               // +0x0800
};

extern GlobalHashTable* g_hashTable; // DAT_01205968

void* __cdecl Allocate(size_t size); // FUN_009c8e50

void HashTable_Insert(uint32_t param_1)
{
    // Allocate a new node (0xC bytes)
    HashNode* node = (HashNode*)Allocate(0xC);
    if (!node) {
        // Allocation failure – skip insertion (likely early return)
        return;
    }

    // Initialize node fields
    node->field0 = 0;
    node->key = param_1;
    node->next = 0;

    // Compute bucket index (hash modulo 512)
    uint32_t index = param_1 & 0x1FF;

    // Insert at head of the bucket's chain
    node->next = g_hashTable->buckets[index];
    g_hashTable->buckets[index] = node;

    // Increment total node count
    g_hashTable->count++;
}