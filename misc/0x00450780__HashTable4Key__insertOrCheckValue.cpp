// FUNC_NAME: HashTable4Key::insertOrCheckValue
// Function at 0x00450780: Hash table insert or find operation.
// This class stores nodes with a 4-int key and 1-int value. 
// Chained hash table with separate free list.
// Struct offsets: this+0x4 = capacity (modulus), this+0x8 = bucket array pointer,
// this+0xC = free list head, this+0x10 = count of allocated nodes.
// Node layout (6 ints): key1 (0), key2 (4), key3 (8), key4 (12), value (16), next (20).

char HashTable4Key::insertOrCheckValue(int key1, int key2, int key3, int key4, int value)
{
    // Hash index based on sum of first and fourth key components
    uint index = (uint)(key1 + key4) % this->capacity;
    Node* node = this->bucketArray[index];
    
    while (true) {
        if (node == nullptr) {
            // No node in this bucket: allocate from free list
            node = this->freeListHead;
            if (node == nullptr) {
                // Free list empty, call allocator (e.g., memory pool expander)
                FUN_00450950();
                node = this->freeListHead;
            }
            // Remove node from free list
            this->freeListHead = (Node*)node->next;
            
            // Initialize new node: clear all fields (size = 6 ints)
            node->key1 = 0;
            node->key2 = 0;
            node->key3 = 0;
            node->key4 = 0;
            node->value = 0;
            node->next = nullptr;
            
            // Increment node count
            this->nodeCount++;
            
            // Set key and value
            node->value = value;
            node->key1 = key1;
            node->key4 = key4;     // Note: key4 set after key1?
            node->key2 = key2;
            node->key3 = key3;
            
            // Insert at head of bucket chain
            node->next = this->bucketArray[index];
            this->bucketArray[index] = node;
            
            return 0; // Inserted new node
        }
        
        // Check if current node's key matches the given key
        if (node->key1 == key1 && node->key2 == key2 && 
            node->key3 == key3 && node->key4 == key4) {
            break; // Found matching key
        }
        node = (Node*)node->next; // Move to next in chain
    }
    
    // Key already exists; return 2 if value matches, 1 otherwise
    return (node->value == value) + 1;
}