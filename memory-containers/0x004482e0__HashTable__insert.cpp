// FUNC_NAME: HashTable::insert

void HashTable::insert(HashTableNode* node)
{
    // Get a random 128-bit key for the node
    uint128_t* newKey = generateRandom128();
    
    // Pointer to the bucket array
    BucketNode** buckets = this->buckets; // +0x70
    uint32_t bucketCount = this->bucketCount; // +0x74
    uint32_t& size = this->size; // +0x78
    
    // Hash the key to get initial bucket index
    uint32_t index = hash128(newKey) % bucketCount;
    BucketNode* existing = buckets[index];
    
    // Search the bucket chain for a node with the same key
    while (existing != nullptr)
    {
        // Get the key of the existing node (stored at beginning of node)
        uint128_t* existingKey = reinterpret_cast<uint128_t*>(existing);
        
        // Compare keys
        if (newKey->val0 == existingKey->val0 && 
            newKey->val1 == existingKey->val1 && 
            newKey->val2 == existingKey->val2 && 
            newKey->val3 == existingKey->val3)
        {
            // Key already exists; insert the node into the ordering list
            node->nextOrder = existing->nextOrder; // +0x10
            node->prevOrder = existing;           // +0x0c
            if (existing->nextOrder != nullptr)
            {
                existing->nextOrder->prevOrder = node;
            }
            existing->nextOrder = node;
            return;
        }
        existing = existing->nextBucket; // +0x18
    }
    
    // If no duplicate found, insert at the head of the bucket chain
    // Resize the hash table if needed (auto-resize flag + threshold)
    if (this->autoResize && size * 2 >= bucketCount) // +0x7c
    {
        resizeHashTable(&this->buckets); // +0x70 pointer
        // Recompute index after resize
        index = hash128(newKey) % this->bucketCount;
    }
    
    // Insert node at bucket head
    node->nextBucket = this->buckets[index]; // +0x18
    this->buckets[index] = node;
    size++;
}