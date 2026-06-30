// FUNC_NAME: EntityDataManager::setObjectTransformData
void EntityDataManager::setObjectTransformData(uint objectId, const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4)
{
    // Global singleton pointer to the hash table manager (DAT_01223398)
    // The manager has a bucket array at offset +0x4 of *(base+8), with size at offset +0x8
    uint bucketIndex = objectId % *(uint*)(*(int*)(g_EntityDataManager[2]) + 8);
    uint** bucketArray = *(uint***)(*(int*)(g_EntityDataManager[2]) + 4);
    uint* node = bucketArray[bucketIndex];

    // Traverse the linked list to find the matching key
    while (node != nullptr)
    {
        if (*node == objectId)
        {
            // Found existing entry – get the data block pointer
            uint dataBlock = node[1];
            // Copy the four vectors to the data block
            *(Vector4*)(dataBlock + 0x30) = row1;  // +0x30
            *(Vector4*)(dataBlock + 0x40) = row2;  // +0x40
            *(Vector4*)(dataBlock + 0x50) = row4;  // +0x50 (note: swapped with row3)
            *(Vector4*)(dataBlock + 0x60) = row3;  // +0x60
            // Mark the data as valid
            *(uint8*)(dataBlock + 0x98) = 1;
            return;
        }
        node = (uint*)node[2]; // next node
    }

    // If not found (should not happen – entry must exist)
    // The original code would write to address 0 here, likely a bug or missing allocation.
    // We assume the caller ensures the entry exists.
}