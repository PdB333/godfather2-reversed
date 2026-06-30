// FUNC_NAME: HashTableSet::insertNode

void __thiscall HashTableSet::insertNode(KeySource* keySource, Node* node, uint32_t additionalKey, void* pExtra /* passed in EAX */)
{
    // Increment the total insert counter in the primary table structure
    keySource->counter28 += 1;  // +0x28
    
    // Mark the node as having been inserted (flag bit 0x20000000)
    node->flags14 |= 0x20000000;  // +0x14
    
    // Copy the 16-byte key from keySource into the node's key fields
    node->key0  = keySource->key[0];  // +0x20
    node->key4  = keySource->key[1];  // +0x24
    node->key8  = keySource->key[2];  // +0x28
    node->keyC  = keySource->key[3];  // +0x2C
    
    // Process additional insertion based on pExtra
    if (pExtra != nullptr)
    {
        if ((*(uint8_t*)((uint8_t*)pExtra + 0x1C) & 4) == 0)
        {
            // ---- Hash table 1: indexed by keySource's hash ----
            uint32_t hash = hashFunction(keySource);  // FUN_004209c0
            uint32_t bucketIndex = hash % this->hashTableSize1;  // +0x74
            uint32_t* bucketPtr = (uint32_t*)(this->hashTableArray1 + bucketIndex * 4);  // +0x70
            
            uint32_t current = *bucketPtr;
            // Search for existing node with matching key
            while (current != 0)
            {
                Node* existingNode = getNode(current);  // FUN_0043ab10 returns address of key? Actually returns Node*
                if (existingNode->key0 == keySource->key[0] &&
                    existingNode->key4 == keySource->key[1] &&
                    existingNode->key8 == keySource->key[2] &&
                    existingNode->keyC == keySource->key[3])
                {
                    break;  // found matching key
                }
                current = *(uint32_t*)(current + 0x18);  // next in chain
            }
            
            // Now search for exact match on additionalKey within that chain
            uint32_t match = current;
            while (match != 0)
            {
                if (*(uint32_t*)(match + 8) == additionalKey)
                    break;
                match = *(uint32_t*)(match + 0x10);
            }
            
            // Insert node into the doubly-linked list at the matched node's bucket
            uint32_t* bucketLink = (uint32_t*)(match + 0x14);
            node->prev10 = *(Node**)(match + 0x14);  // +0x10
            node->next14 = bucketLink;               // +0x14? actually +0xC and +0x10?
            // The code sets param_3+0x10 = *(match+0x14) and param_3+0xC = pointer to that field
            if (*bucketLink != 0)
            {
                *(uint32_t**)(*bucketLink + 0xC) = (uint32_t*)&node->next14;  // link back
            }
            *bucketLink = (uint32_t)node;
        }
        else
        {
            // ---- Hash table 2: indexed by node's key hash ----
            uint32_t size2 = this->hashTableSize2;  // +0x84
            uint32_t* array2 = (uint32_t*)(this->hashTableArray2);  // +0x80
            uint32_t hash2 = hashFunction(&node->key0);  // hash of node's 16-byte key
            uint32_t bucketIndex2 = hash2 % size2;
            
            // Optional resize if load factor > 2?
            if (this->rehashFlag2 != 0 && (size2 * 2 <= this->count2))  // +0x8C, +0x88
            {
                resizeHashTable2(&array2);  // FUN_00448fc0
                hash2 = hashFunction(&node->key0);
                bucketIndex2 = hash2 % this->hashTableSize2;
            }
            
            // Insert node into the singly-linked list of bucket
            node->next30 = *(Node**)(array2 + bucketIndex2);  // +0x30
            *(uint32_t**)(array2 + bucketIndex2) = &node;    // overwrite bucket
            this->count2 += 1;  // +0x88
        }
    }
    
    // ---- Global counter and finalize node with additionalKey ----
    this->totalInsertCountCC += 1;  // +0xCC
    node->additionalKey1C = additionalKey;  // +0x1C
    
    // ---- Hash table 3: indexed by additionalKey ----
    uint32_t* array3 = (uint32_t*)(this->hashTableArray3);  // +0x48
    uint32_t size3 = this->hashTableSize3;                  // +0x4C
    uint32_t bucketIndex3 = additionalKey % size3;
    
    // Search for existing bucket with key == additionalKey
    uint32_t* bucketNode = (uint32_t*)*(array3 + bucketIndex3);
    while (bucketNode != nullptr)
    {
        if (*bucketNode == additionalKey)
        {
            // Found existing bucket. Link node into its list.
            goto link_into_bucket;
        }
        bucketNode = (uint32_t*)bucketNode[6];  // next in bucket chain
    }
    
    // No bucket found, allocate a new bucket node
    uint32_t* newBucket = (uint32_t*)allocateBucket();  // FUN_00448cd0
    uint32_t* bucketData = newBucket + 1;  // fields: [0]=key, [1]=next, [2]=prev, [3]=key again?, [4]=?, [5]=?, [6]=nextInHash?
    // The code has a check: if (local_14 != bucketData) ... local_14 is a local array
    // Let's assume it's a temporary
    *bucketData = 0;
    newBucket[2] = 0;
    newBucket[3] = additionalKey;
    newBucket[4] = 0;
    newBucket[5] = 0;
    newBucket[0] = additionalKey;
    newBucket[6] = *(uint32_t*)(array3 + bucketIndex3);  // link into hash chain
    *(uint32_t**)(array3 + bucketIndex3) = newBucket;
    
    // Insert into global doubly-linked list of buckets
    *bucketData = (uint32_t)this->bucketListHead;  // +0x60
    newBucket[2] = 0;
    if (this->bucketListHead == 0)
    {
        this->bucketListTail = bucketData;  // +0x64? actually +100 decimal = 0x64
    }
    else
    {
        *(uint32_t**)(this->bucketListHead + 4) = bucketData;
    }
    this->bucketListHead = bucketData;
    
    // Fall through to link node into bucket
link_into_bucket:
    uint32_t* bucketKey = bucketData + 3;  // points to bucket's key field
    node->keyValue8 = *bucketKey;  // +0x8
    node->prevPtr4 = bucketData;   // +0x4 (next in node list? actually link to bucket)
    if (*bucketKey != 0)
    {
        *(uint32_t**)(*bucketKey + 4) = (uint32_t*)&node->keyValue8;
    }
    *bucketKey = (uint32_t)node;
    
    // Optional callback
    if (gInsertCallback != nullptr)  // DAT_012053ec
        gInsertCallback();
}