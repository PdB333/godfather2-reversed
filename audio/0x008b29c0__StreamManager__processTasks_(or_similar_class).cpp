// FUNC_NAME: StreamManager::processTasks (or similar class)
// Address: 0x008b29c0
// Role: Iterates through tasks/items in a stream, initializing and processing until completion.
//   This method sets a field at offset +0x64 (m_pCurrentItem) from data in a stream item.
//   Likely part of a streaming/loading manager (BNKStreamManager or MultiTrackStream).

void __thiscall StreamManager::processTasks(void* this, void* pStreamManager)
{
    char bFinished; // cVar1
    void* pItem; // iVar2

    // Initialize the stream manager object
    initializeStreamManager(pStreamManager);

    // Register the stream class/hash (0xD12C85FE = FourCC for stream type)
    setStreamClassId(pStreamManager, 0xd12c85fe);

    // Loop until stream processing is finished
    bFinished = isStreamFinished();
    while (bFinished == '\0') {
        // Advance to the next item in the stream queue
        advanceStreamCursor(); // getNextItem() without storing return value

        // Check if the current item is valid
        if (isCurrentItemValid() == 0) {
            // If not valid, get the next item and set our active buffer
            pItem = getNextStreamItem(); // now stores return value
            *(void**)((int)this + 0x64) = *(void**)((int)pItem + 8); // copy field at offset 8 (e.g., a handle or pointer)
        }

        // Process the current item (e.g., decode, feed to downstream)
        processStreamItem();

        // Re-check completion status
        bFinished = isStreamFinished();
    }
}