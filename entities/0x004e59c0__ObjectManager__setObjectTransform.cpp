// FUNC_NAME: ObjectManager::setObjectTransform
void ObjectManager_setObjectTransform(uint objectID, float* transformPart1, float* transformPart2, float* transformPart3, float* transformPart4)
{
    // Global singleton: g_objectManager at 0x01223398
    // This structure contains a hash table for object lookup.
    // Offsets: +0x08 -> ptr to internal hashtable struct
    // Internal struct: +0x04 -> ptr to array of bucket heads; +0x08 -> number of buckets
    // Each bucket head is a linked list of nodes (HashNode)
    // HashNode: [0] = key (object ID), [4] = data pointer (object instance), [8] = next node pointer

    uint32_t* hashTableHeader = *(uint32_t**)(*(int*)(DAT_01223398 + 8) + 4);
    uint32_t numBuckets = *(uint32_t*)(*(int*)(DAT_01223398 + 8) + 8);
    uint32_t bucketIndex = objectID % numBuckets;

    uint32_t* node = *(uint32_t**)(hashTableHeader + bucketIndex * 4);

    while (node != nullptr)
    {
        if (node[0] == objectID)
        {
            // Found the node; the data pointer is at offset +4
            if (node != nullptr && (node + 1) != nullptr)
            {
                uint32_t objData = node[1];  // data pointer stored at node[1]
                if (objData != 0)
                {
                    // Copy the four 16-byte transformation blocks into the object
                    // Offsets relative to objData:
                    // +0x30: transformPart1 (e.g., position/row0)
                    // +0x40: transformPart2 (e.g., rotation/row1)
                    // +0x60: transformPart4 (e.g., scale/row3?) – note order is swapped
                    // +0x50: transformPart3 (e.g., third row?) 
                    // This might be a 4x4 matrix stored with row order: part1, part2, part3, part4
                    // but the copy order here is deliberately part1, part2, part4, part3.
                    // Possibly due to column-major vs row-major or specific engine layout.

                    // Copy transformPart1 (16 bytes) to offset 0x30
                    *(float*)(objData + 0x30) = transformPart1[0];
                    *(float*)(objData + 0x34) = transformPart1[1];
                    *(float*)(objData + 0x38) = transformPart1[2];
                    *(float*)(objData + 0x3C) = transformPart1[3];

                    // Copy transformPart2 to offset 0x40
                    *(float*)(objData + 0x40) = transformPart2[0];
                    *(float*)(objData + 0x44) = transformPart2[1];
                    *(float*)(objData + 0x48) = transformPart2[2];
                    *(float*)(objData + 0x4C) = transformPart2[3];

                    // Copy transformPart4 to offset 0x60
                    *(float*)(objData + 0x60) = transformPart4[0];
                    *(float*)(objData + 0x64) = transformPart4[1];
                    *(float*)(objData + 0x68) = transformPart4[2];
                    *(float*)(objData + 0x6C) = transformPart4[3];

                    // Copy transformPart3 to offset 0x50
                    *(float*)(objData + 0x50) = transformPart3[0];
                    *(float*)(objData + 0x54) = transformPart3[1];
                    *(float*)(objData + 0x58) = transformPart3[2];
                    *(float*)(objData + 0x5C) = transformPart3[3];

                    // Mark the object's transform as updated / dirty (flag at +0x98)
                    *(uint8_t*)(objData + 0x98) = 1;
                }
            }
            else
            {
                goto search_failed;
            }
            return;
        }
        node = (uint32_t*)node[2]; // next node in bucket
    }

search_failed:
    // Object with the given ID was not found in the hash table – do nothing
    return;
}