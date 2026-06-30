// FUNC_NAME: ObjectDataManager::setObjectData

// Reconstructed C++ for function at 0x004ed8b0
// This function appears to update or insert data in a hash table keyed by an unsigned integer.
// The hash table is stored in a global manager structure at DAT_01223398.
// The function copies 16 bytes from param_5 (a pointer to a struct of 4 uint32) into the data block
// at offsets 0x10-0x1c, and sets additional fields at offsets 0x20, 0x28, 0x30, 0x2c, 0x34, 0x3c.
// NOTE: There is a potential null pointer dereference in the failure path (LAB_004ed8e3),
// which suggests the caller only invokes this for existing entries.

struct HashNode {
    uint32_t key;            // +0x00
    uint32_t* dataPtr;       // +0x04 - pointer to data block
    HashNode* next;          // +0x08
};

struct ObjectDataManager {
    // Layout from DAT_01223398 + 8
    // +0x00: some base pointer (not used here)
    // +0x04: HashNode** bucketArray;    // pointer to array of pointers to head nodes
    // +0x08: uint32_t numBuckets;       // number of buckets in the hash table
    char unknown[8];
    HashNode** bucketArray;  // +0x08? Actually +8 from start of outer struct, then +4 and +8 relative to that
    uint32_t numBuckets;     // +0x0C? Let's re-derive from code:
    // Code: *(int *)(DAT_01223398 + 8) gives a pointer to some substructure.
    // Then *(int *)((sub)+4) is bucketArray, *(int *)((sub)+8) is numBuckets.
    // So the substructure has: +0: ?, +4: bucketArray, +8: numBuckets.
};

// Global manager instance (in .data section at DAT_01223398)
extern ObjectDataManager g_ObjectDataManager;

void ObjectDataManager::setObjectData(uint32_t key, 
                                       uint32_t param_2,
                                       const uint32_t* param_5,   // pointer to 4 uint32 block
                                       uint32_t param_6,
                                       uint32_t param_7,
                                       uint32_t param_8,
                                       uint32_t param_9,
                                       uint8_t param_10)
{
    // Derive global substructure pointer
    void* base = *(void**)(DAT_01223398 + 8);
    uint32_t* bucketArray = *(uint32_t**)((int)base + 4);
    uint32_t numBuckets  = *(uint32_t*)((int)base + 8);

    // Hash bucket index
    uint32_t bucketIndex = key % numBuckets;
    
    // Start searching in the bucket
    uint32_t* nodePtr = (uint32_t*)bucketArray[bucketIndex];
    uint32_t dataPtr;

    while (true) {
        if (nodePtr == nullptr) {
            // No node found — this should not happen; leads to null write.
            dataPtr = 0;
        } else if (*nodePtr == key) {
            // Found node; retrieve data pointer (at offset +4)
            if (nodePtr != nullptr && (nodePtr + 1) != nullptr) {
                dataPtr = nodePtr[1];  // dataPtr from node
                break;
            } else {
                dataPtr = 0;
            }
        } else {
            // Continue to next node in chain (node[2] is next pointer)
            nodePtr = (uint32_t*)nodePtr[2];
            continue;
        }
        break;
    }

    // Copy 16 bytes from param_5 into offsets 0x10-0x1c of data block
    uint32_t* dest = (uint32_t*)(dataPtr + 0x10);
    dest[0] = param_5[0];
    dest[1] = param_5[1];
    dest[2] = param_5[2];
    dest[3] = param_5[3];

    // Set remaining fields
    *(uint32_t*)(dataPtr + 0x20) = param_2;
    *(uint32_t*)(dataPtr + 0x28) = param_7;
    *(uint32_t*)(dataPtr + 0x30) = param_6;
    *(uint32_t*)(dataPtr + 0x2c) = param_8;
    *(uint32_t*)(dataPtr + 0x34) = param_9;
    *(uint8_t*)(dataPtr + 0x3c) = param_10;
}