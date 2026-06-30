// FUNC_NAME: ResourceManager::allocateAndInsertHandle

void ResourceManager::allocateAndInsertHandle(uint hashKey)
{
    // Handle entry structure: [key, flags, allocSize, reserved]
    uint handleEntry[4];
    handleEntry[1] = 2;          // Allocation flags (e.g., alignment requirement)
    handleEntry[2] = 0x10;       // Allocation size (16-byte block)
    handleEntry[3] = 0;          // Reserved

    // Allocate 0xC0 bytes from the resource pool using the descriptor.
    // FUN_009c8ed0 returns a handle (pointer) or null on failure.
    void* pHandle = staticAllocate(0xC0, &handleEntry[1]);

    uint uniqueId;
    if (pHandle == nullptr) {
        uniqueId = 0;
    } else {
        // Generate a unique identifier for this resource.
        uniqueId = generateUniqueId();
    }

    handleEntry[0] = hashKey;

    // Retrieve bucket count from the global hash table.
    // Global layout: g_pResourceManager (+0x0) -> m_pHashTable (+0x8) -> m_bucketCount (+0x8)
    ResourceManager* pManager = *reinterpret_cast<ResourceManager**>(DAT_01223398);
    HashTable* pHashTable = pManager->pHashTable;  // offset +0x8
    uint bucketCount = pHashTable->bucketCount;     // offset +0x8

    // Compute bucket index by modulo.
    uint bucketIndex = hashKey % bucketCount;

    // Insert the entry into the hash table: key, value (uniqueId), bucket index.
    hashTableInsertEntry(handleEntry, &uniqueId, bucketIndex);
}