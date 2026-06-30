// FUNC_NAME: AnimationDataManager::setNodeTransform
void AnimationDataManager::setNodeTransform(uint nodeHash, const float transform1[4], const float transform2[4])
{
    // Global manager pointer at 0x01223398
    // Structure layout:
    // +0x0: some vftable or data
    // +0x8: pointer to hash table bucket array
    //   +0x4: pointer to bucket array (each bucket is an array of bucket heads)
    //   +0x8: number of buckets
    // Each bucket head is a linked list node (struct Node):
    //   [0]: key (nodeHash)
    //   [1]: data pointer (NodeData)
    //   [2]: next node pointer
    // NodeData layout:
    //   +0x00: ?
    //   ... (skipping)
    //   +0x24: pointer to some sub-object with +0x4C field
    //   +0x30: transform1 (position? quaternion?) 4 floats
    //   +0x50: transform2 (quaternion? translation?) 4 floats
    //   +0x98: byte flag (dirty/updated marker)

    // Hash table lookup
    uint* bucketArray = *(uint**)(*(int*)(DAT_01223398 + 8) + 4);
    uint bucketCount = *(uint*)(*(int*)(DAT_01223398 + 8) + 8);
    uint bucketIndex = nodeHash % bucketCount;
    uint* currentNode = (uint*)bucketArray[bucketIndex];

    uint nodeDataPtr = 0; // Default to nullptr if not found

    while (currentNode != nullptr)
    {
        if (*currentNode == nodeHash)
        {
            // Found matching hash
            if (currentNode != nullptr && (currentNode + 1) != nullptr)
            {
                nodeDataPtr = currentNode[1]; // Get data pointer from node
            }
            break;
        }
        currentNode = (uint*)currentNode[2]; // Next node in chain
    }

    // Write transform data to node's data block
    // If not found, nodeDataPtr is 0 and writes would be invalid;
    // assumed that the caller ensures the hash exists in the table.
    float* data = (float*)nodeDataPtr;
    data[0x30/4] = transform1[0];
    data[0x34/4] = transform1[1];
    data[0x38/4] = transform1[2];
    data[0x3C/4] = transform1[3];

    data[0x50/4] = transform2[0];
    data[0x54/4] = transform2[1];
    data[0x58/4] = transform2[2];
    data[0x5C/4] = transform2[3];

    // Set a property in a sub-object referenced at +0x24
    uint* subObject = *(uint**)(nodeDataPtr + 0x24);
    if (subObject != nullptr)
    {
        *(float*)((uint)subObject + 0x4C) = transform2[3]; // Use last component
    }

    // Mark node data as updated
    *(byte*)(nodeDataPtr + 0x98) = 1;
}