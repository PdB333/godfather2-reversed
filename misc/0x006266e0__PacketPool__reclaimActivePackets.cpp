// FUNC_NAME: PacketPool::reclaimActivePackets
int PacketPool::reclaimActivePackets()
{
    int totalFreedSize = 0;
    // m_poolHeader is at this+0x10, it's a pointer to a PoolHeader struct
    PoolHeader* pool = *(PoolHeader**)(this + 0x10);
    PacketNode** ppCurrent = &pool->activeHead; // offset +0x10
    PacketNode* pNode = *ppCurrent;
    PacketNode* pPrev = nullptr;
    // Build a chain of removed nodes (to prepend to free list)
    PacketNode* pFirstRemoved = nullptr; // local_4
    PacketNode* pLastRemovedNext = &pFirstRemoved; // local_8, pointer to pointer

    while (pNode != nullptr) {
        pPrev = (PacketNode*)ppCurrent; // save pointer to the pointer that points to current node
        // Check flags at node+0x05
        if ((*(byte*)((int)pNode + 5) & 0x11) == 0 && (*(byte*)((int)pNode + 5) & 0x02) != 0) {
            // node->data is at offset +0x08 (pNode[2] as undefined4*)
            PacketData* data = (PacketData*)pNode->data;
            // Check flag at data+0x06
            if ((*(byte*)((int)data + 6) & 0x04) == 0) {
                // Call external function to check if the data is still referenced
                uint64_t result = FUN_00637f90(); // returns a struct with an int at offset 0
                if (*(int*)result != 0) {
                    int dataSize = pNode->size; // offset +0x0C (pNode[3])
                    // Remove node from active list
                    *ppCurrent = pNode->next;
                    pNode->next = nullptr;
                    totalFreedSize += dataSize + 0x10;
                    // Append the removed node to the local chain (prepend later)
                    *pLastRemovedNext = pNode;
                    pLastRemovedNext = (PacketNode**)pNode; // now points to node's first field (next)
                    // Continue without advancing ppCurrent (already updated)
                    pNode = *ppCurrent;
                    continue; // skip the flag clear below
                } else {
                    // Set the data object's flag to indicate it's not reusable
                    ((byte*)data)[6] |= 0x04;
                }
            }
            // Clear the 'used' flag bit (0x02) in the node
            ((byte*)pNode)[5] &= 0xFD;
        }
        // Advance to next node
        ppCurrent = &pNode->next;
        pNode = *ppCurrent;
    }

    // Prepend the removed chain to the free list
    // pool->freeHead is at offset +0x14
    if (pFirstRemoved != nullptr) {
        *pLastRemovedNext = pool->freeHead; // link chain tail to old free head
        pool->freeHead = pFirstRemoved;     // new free head is first removed node
    }

    return totalFreedSize;
}