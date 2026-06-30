// FUNC_NAME: HashTable::insert
// Function address: 0x004e0cd0
// Role: Inserts a value into a hash table with separate chaining, using a free list for nodes.
// The hash table supports dynamic resizing when load factor exceeds threshold.

class HashTable {
public:
    struct Node {
        void* data;      // +0x00
        Node* next;      // +0x04
    };

    Node** buckets;      // +0x00: array of bucket heads
    int bucketCount;     // +0x04: number of buckets
    Node* freeList;      // +0x08: linked list of free nodes
    int elementCount;    // +0x0C: number of stored elements
    char unknownFlag;    // +0x14: some flag (checked for non-zero)

    // Internal helpers (declared elsewhere)
    void rehash();                // FUN_004e1140
    int computeIndex(void* key);  // FUN_004e0dd0
    Node* allocateNode();         // FUN_004e0d90

    void insert(void* key, void* value) {
        int index;

        // If flag is set and load factor exceeds 2x (bucketCount*2 <= elementCount), rehash
        if (unknownFlag != '\0' && (bucketCount * 2) <= elementCount) {
            rehash();
            index = computeIndex(key);
        }

        // Get a node from the free list; if empty, allocate a new one
        Node* node = freeList;
        if (node == nullptr) {
            allocateNode();
            node = freeList;
        }

        // Remove node from free list
        freeList = node->next;
        node->next = nullptr;
        elementCount++;

        // Set node data
        node->data = value;

        // Insert node into bucket at computed index (head insertion)
        node->next = buckets[index];
        buckets[index] = node;
    }
};