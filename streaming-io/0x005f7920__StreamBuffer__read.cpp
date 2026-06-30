// FUNC_NAME: StreamBuffer::read
uint StreamBuffer::read(uint sizeToRead)
{
    uint totalRead = 0;
    BufferNode* pNode = m_pSentinel->pNext;

    if (sizeToRead == 0) {
        return 0;
    }

    do {
        // Sentinel check – if we wrapped back to the sentinel without enough data, abort
        if (pNode == m_pSentinel) {
            // Unreachable in normal operation; error path
            reportStreamError();
            return totalRead;
        }

        // Assert that pNode is valid (extra safety, matches debug build)
        if (pNode == m_pSentinel) {
            reportStreamError();
        }

        // Only read from buffers that are "readable" (some internal flag at +0x38 == 0)
        if (pNode->pData->isReadable) {
            uint bytesRead = pNode->pData->read(sizeToRead - totalRead);
            totalRead += bytesRead;
        }

        // Step to next node (linked list, circular with sentinel)
        if (pNode == m_pSentinel) {
            reportStreamError();
        }
        pNode = pNode->pNext;
    } while (totalRead < sizeToRead);

    return totalRead;
}