// FUNC_NAME: StreamManager::loadStreamBlock
uint StreamManager::loadStreamBlock(StreamHandle* handle)
{
    uint32_t status;
    uint32_t* headerPtr;
    int allocBlock;
    uint32_t signature1;
    uint32_t signature2;
    uint32_t signature3;
    uint32_t signature4;

    // Check if the stream block is already loaded (bit 23 of flags)
    status = (handle->flags >> 0x17) & 1;
    if ((status & 1) == 0) {
        // Check if the stream is available for reading
        status = isStreamAvailable();
        if (status != 0) {
            // Acquire a lock on the stream manager
            void* lockObj = getStreamLock();
            lockStreamMutex(lockObj);

            // Get pointer to the header data from the stream buffer
            headerPtr = (uint32_t*)getStreamHeader();

            // Check if the header already contains valid signatures or is empty
            signature1 = headerPtr[0];
            signature2 = headerPtr[1];
            signature3 = headerPtr[2];
            signature4 = headerPtr[3];

            if (((signature1 != kStreamBlockSignature1) ||
                 (signature2 != kStreamBlockSignature2) ||
                 (signature3 != kStreamBlockSignature3) ||
                 (signature4 != kStreamBlockSignature4)) &&
                ((signature1 != 0 || signature2 != 0) ||
                 (signature3 != 0 || signature4 != 0))) {
                // No valid header and not empty; need to load the block
                if (this->m_readyFlag == 0) {
                    this->m_progress = 0;
                }

                // Allocate a new stream block
                allocBlock = allocateStreamBlock();

                // Process the stream header into the handle
                processStreamHeader(handle);

                // Copy the signature data into the allocated block
                *(uint32_t*)(allocBlock + 8) = signature1;
                *(uint32_t*)(allocBlock + 0xc) = signature2;
                *(uint32_t*)(allocBlock + 0x10) = signature3;
                *(uint32_t*)(allocBlock + 0x14) = signature4;

                // Mark stream block as complete (set bit 26)
                handle->flags |= kFlagStreamComplete;

                // Return combination: high 24 bits of signature1 with low byte = 1 (success)
                return (signature1 & 0xffffff00) | 1;
            }

            // Header already valid or empty: return the high 24 bits of the first signature
            return signature1 & 0xffffff00;
        }

        // Stream not available; mark as "loaded" to skip future attempts (bit 23)
        handle->flags |= kFlagStreamLoaded;
    }

    // Already loaded (bit 23 set) or stream not available
    return status & 0xffffff00;
}