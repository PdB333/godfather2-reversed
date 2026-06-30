// FUNC_NAME: HashTableManager::insert
void HashTableManager::insert(uint key, uint value)
{
    // Global hash table manager pointer (singleton)
    int* manager = DAT_01205968;
    uint tableSize = *(uint*)(manager + 0x808);          // +0x808: hash table size (modulus)
    uint hashIndex = key % tableSize;

    uint* freeNode = *(uint**)(manager + 0x810);         // +0x810: free list head
    if (freeNode == nullptr)
    {
        // Allocate a new block: 256 nodes (12 bytes each) + 4 bytes extra
        int* newBlock = (int*)FUN_009c8e50(0xC04);       // custom allocator (likely malloc)
        // Initialize free list within the block (each node is 3 ints: key, value, next)
        int* node = newBlock;
        for (int i = 0; i < 256; i++)
        {
            node[3] = (int)(node + 4);                   // set next pointer to next node
            node += 3;
        }
        newBlock[0x300] = 0;                             // last int in block set to 0 (unused?)
        // Link block into block list (for later deallocation)
        *newBlock = *(int*)(manager + 0x818);            // +0x818: block list head
        *(int**)(manager + 0x818) = newBlock;
        // Set free list head to first node in new block
        freeNode = (uint*)(newBlock + 1);
        *(uint**)(manager + 0x810) = freeNode;
    }

    // Remove node from free list
    *(uint**)(manager + 0x810) = (uint*)freeNode[2];    // freeNode[2] is next pointer

    // Initialize node fields
    freeNode[0] = key;                                   // key
    freeNode[1] = value;                                 // value
    // Insert into hash bucket (chaining)
    uint* bucketArray = *(uint**)(manager + 0x80c);      // +0x80c: bucket array pointer
    freeNode[2] = bucketArray[hashIndex];                // next = current bucket head
    bucketArray[hashIndex] = (uint)freeNode;             // bucket head = new node

    // Increment total element count
    *(int*)(manager + 0x814) += 1;                       // +0x814: element count
}