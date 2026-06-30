// FUNC_NAME: StreamManager::readBytes
uint __thiscall StreamManager::readBytes(uint maxBytes)
{
    // this->m_pHeadNode at offset 0x4c (pointer to circular linked list of StreamNode)
    // Each StreamNode: offset 0: next pointer, offset 8: pointer to BufferData
    // BufferData: offset 0x38: flag (0 = data available)

    StreamNode** ppHead = *(StreamNode***)((uint)this + 0x4c);
    StreamNode* pNode = (StreamNode*)*(uint*)ppHead; // first node
    uint totalRead = 0;

    if (maxBytes != 0) {
        do {
            // Check if we've wrapped around to the head (circular list end)
            if (pNode == (StreamNode*)*(uint*)ppHead) {
                break; // no more data
            }

            // Debug assertion: pNode should not be head here
            if (pNode == (StreamNode*)*(uint*)ppHead) {
                debugAssert(); // FUN_00b97aea
            }

            // Get the buffer associated with this node
            void* pBufferData = *(void**)((uint)pNode + 8); // puVar3[2]
            // Check if data is ready (flag at +0x38 == 0)
            if (*(int*)((uint)pBufferData + 0x38) == 0) {
                int bytesRead = readFromBufferChunk(pBufferData, maxBytes - totalRead); // FUN_005f8520
                totalRead += bytesRead;
            }

            // Another debug check
            if (pNode == (StreamNode*)*(uint*)ppHead) {
                debugAssert();
            }

            // Advance to next node
            pNode = (StreamNode*)pNode->pNext; // *puVar3
        } while (totalRead < maxBytes);
    }

    return totalRead;
}