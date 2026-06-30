// FUNC_NAME: ObjectPool::insert
// Address: 0x006e7830
// Role: Insert an object into a hash bucket, using a precomputed hash index.
// The pool supports automatic expansion when count >= 2*capacity.
// Memory nodes are managed via a free list.

class ObjectPool {
public:
    struct PoolNode {
        void* value;          // +0x00
        PoolNode* next;       // +0x04
    };

    // offsets relative to 'this'
    PoolNode** m_buckets;     // +0x00: array of bucket heads (size = m_capacity)
    int m_capacity;           // +0x04: number of buckets
    PoolNode* m_freeList;     // +0x08: head of free node list
    int m_count;              // +0x0C: number of allocated nodes
    int m_unknown;            // +0x10: unused in this function
    bool m_active;            // +0x14: flag enabling automatic expansion

    // internal helpers (not defined here)
    void expand();
    unsigned int computeHash(unsigned int key);
    void allocateFreeNode(); // ensures m_freeList is non-null
};

void __thiscall ObjectPool::insert(unsigned int key, void* value, unsigned int hashIndex) {
    // If the pool is active and has grown beyond 2x capacity, expand and recompute hash
    if (m_active && (m_capacity * 2 <= m_count)) {
        expand();                                 // FUN_006e6f20
        hashIndex = computeHash(key);            // FUN_006e6010 (new bucket index)
    }

    // Obtain a free node from the free list
    PoolNode* node = m_freeList;                  // param_1[2]
    if (node == nullptr) {                       // free list empty
        allocateFreeNode();                       // FUN_006e73f0
        node = m_freeList;                        // re-fetch after allocation
    }

    // Remove node from free list
    m_freeList = node->next;                     // param_1[2] = node->next

    // Clear next pointer (optional, but done in original)
    node->next = nullptr;                        // puVar1[1] = 0

    // Increment total node count
    m_count++;

    // Fill the node with value
    node->value = value;                         // puVar1[0] = param_3

    // Insert node at head of the corresponding bucket
    node->next = m_buckets[hashIndex];           // node->next = current head
    m_buckets[hashIndex] = node;                 // new head = node
}