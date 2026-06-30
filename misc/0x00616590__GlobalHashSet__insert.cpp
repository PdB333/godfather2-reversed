// FUNC_NAME: GlobalHashSet::insert
// Function at 0x00616590: Insert a key into a global hash set (512 buckets) with linked list chaining.
// The hash table is at a fixed global address (0x01205968). Nodes are allocated from a pool (FUN_009c8e50) that never fails.
// Node structure: 12 bytes = { int flags, unsigned int key, HashNode* next }
// Bucket index = key & 0x1FF (9 bits). Count at offset 0x800.

struct HashNode {
    int flags;          // +0x00
    unsigned int key;   // +0x04
    HashNode* next;     // +0x08
};

struct GlobalHashTable {
    HashNode* buckets[512]; // +0x00 to +0x7FC
    int count;              // +0x800
};

// Global instance fixed at 0x01205968
GlobalHashTable* const g_hashTable = reinterpret_cast<GlobalHashTable*>(0x01205968);

// Pool allocator: returns 0xC bytes of zeroed memory (never returns null in practice)
extern void* __cdecl FUN_009c8e50(unsigned int size);

__declspec(naked) void GlobalHashSet_insert(unsigned int key) {
    __asm {
        // Original function call is __cdecl, so key is on stack (or register based on compiler)
        // We'll just compile the C++ below and let the compiler handle it
    }
}

// The actual logic (compile with /O2 and no optimization code for signature matching)
void GlobalHashSet_insert_impl(unsigned int key) {
    int bucketIndex = key & 0x1FF;
    HashNode* newNode = static_cast<HashNode*>(FUN_009c8e50(sizeof(HashNode))); // 12 bytes
    newNode->flags = 0;
    newNode->key = key;
    newNode->next = g_hashTable->buckets[bucketIndex];
    g_hashTable->buckets[bucketIndex] = newNode;
    g_hashTable->count++;
}