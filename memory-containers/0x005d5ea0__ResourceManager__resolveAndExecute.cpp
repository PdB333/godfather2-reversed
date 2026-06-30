// FUNC_NAME: ResourceManager::resolveAndExecute
void ResourceManager::resolveAndExecute(uint resourceId, uint32_t contextId, uint32_t* buffer, uint64_t* additionalData)
{
    static volatile uint32_t initFlag = 0;
    static HashNode** bucketArray = nullptr;
    static uint32_t numBuckets = 0;

    // One-time initialization of the hash table
    if ((initFlag & 1) == 0) {
        initFlag |= 1;
        // Set up the bucket array pointer; PTR_FUN_00e36cb4 is likely a function table or sentinel
        bucketArray = (HashNode**)(&PTR_FUN_00e36cb4); // +0x225e10
        // Allocate space for bucket pointers: 0x200 bytes => 128 buckets (assuming 4-byte pointers)
        bucketArray = (HashNode**)FUN_004cfc30(0x200); // custom allocation
        // Register cleanup on exit
        _atexit((_func_4879*)&cleanupFunction);
    }

    // Hash the resource ID to get bucket index
    uint32_t bucketIndex = resourceId % numBuckets;

    // Traverse the chain in this bucket
    HashNode* node = bucketArray[bucketIndex];
    while (node != nullptr) {
        if (node->key == resourceId) {
            goto found;
        }
        node = node->next;
    }

    // Not found: use default value 0
    uVar2 = 0;
    goto process;

found:
    // If node is non-null, extract the stored value (second field)
    if (node != nullptr) {
        uVar2 = node->value;
    } else {
        uVar2 = 0;
    }

process:
    // Copy the 16 uint32s from buffer to a local array
    uint32_t localBuffer[16];
    for (int i = 0; i < 16; i++) {
        localBuffer[i] = buffer[i];
    }

    // Copy the two uint64 values
    uint64_t localAdditional[2];
    localAdditional[0] = additionalData[0];
    localAdditional[1] = additionalData[1];

    // Call the processing function with the looked-up value and the copied data
    FUN_005d2010(uVar2, contextId, localBuffer, localAdditional);
    return;
}