// FUNC_NAME: TNLConnection::serializeReliableChunks
uint TNLConnection::serializeReliableChunks(void) {
    // List head at this+0x48 (doubly linked list of reliable chunks)
    ChunkListNode* listHead = *(ChunkListNode**)(this + 0x48);
    ChunkListNode* currentNode = listHead->next; // next node
    uint bytesWritten = 0;

    do {
        if (currentNode == listHead) {
            // Reached end of list
            return bytesWritten;
        }

        // Debug assertion: check list integrity (head unchanged)
        if (currentNode == *(ChunkListNode**)(this + 0x48)) {
            // AssertFail (FUN_00b97aea)
            __assertFail();
        }

        // Get the chunk object stored at offset +8 in the node
        ReliableChunk* chunk = (ReliableChunk*)currentNode->field_0x8;

        // Virtual call: getDataPointer() (vtable+8)
        void* dataPtr = chunk->vtable->getDataPointer();

        // Check if chunk has data (non-zero at offset +4 in data)
        if (*(int*)((char*)dataPtr + 4) != 0) {
            int remaining = 8 - bytesWritten;

            // Virtual call: getDataSize() (vtable+12)
            int chunkSize = chunk->vtable->getDataSize();

            // Clamp copy size to remaining space in buffer
            int bytesToCopy = (chunkSize < remaining) ? chunkSize : remaining;

            // Copy chunk data into buffer (FUN_006021f0)
            // Parameters: chunk->buffer (offset +4), chunk itself, dataPtr, chunk->field_0x1c, bytesToCopy
            int copied = copyData(chunk->buffer, chunk, dataPtr, chunk->field_0x1c, bytesToCopy);
            bytesWritten += copied;
        }

        // Debug assertion again
        if (currentNode == *(ChunkListNode**)(this + 0x48)) {
            __assertFail();
        }

        // Advance to next node
        currentNode = currentNode->next;
    } while (bytesWritten < 8);

    return bytesWritten;
}