// FUNC_NAME: EntityDataManager::storePackedKey
// Address: 0x00643990
// Constructs a packed key from four components (majorType, category, index, subIndex)
// and stores a data value retrieved from this->m_pHashTable->dataPtr (offset +0x0C then +0x08).
// Bit layout: [majorType (24+ bits)] [category (9 bits)] [index (9 bits)] [subIndex (6 bits)]

void __thiscall EntityDataManager::storePackedKey(int thisPtr, uint majorType, uint category, uint index, uint subIndex)
{
    uint packedKey;
    uint dataValue;
    
    // Build packed key: ((majorType << 9 | category) << 9 | index) << 6 | subIndex
    packedKey = (((majorType << 9) | category) << 9 | index) << 6 | subIndex;
    
    // Retrieve data from internal hash table structure
    // thisPtr + 0x0C: pointer to hash table manager
    // *(hashTablePtr + 0x08): data value to associate with the key
    dataValue = *(uint*)(*(int*)(thisPtr + 0x0C) + 0x08);
    
    // Insert into the key-value store
    FUN_006438e0(packedKey, dataValue);
}