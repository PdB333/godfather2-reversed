// FUNC_NAME: ChunkedDataReader::LoadChunksFromStream

void __thiscall ChunkedDataReader::LoadChunksFromStream(int this, void* stream)
{
    char isEnd;
    int canProcess;
    void* chunkData;

    // Initialize the stream source
    InitializeStream(stream);

    // Set the expected identifier/fourcc for the chunk stream
    SetStreamIdentifier(stream, 0x545C7E0F); // likely a file type signature

    // Loop until the stream end is reached
    isEnd = IsStreamEndReached();
    while (isEnd == 0) {
        // Advance to the next chunk header
        AdvanceStream();

        // Check whether the current chunk should be processed (0 = process, non-zero = skip)
        canProcess = IsChunkAllowed();
        if (canProcess == 0) {
            // Advance again to position at the chunk data
            AdvanceStream();

            // Retrieve the chunk data pointer (or identifier)
            chunkData = GetChunkData();

            // Append the chunk entry to the internal list at offset 0x190
            // This list likely stores loaded chunk references
            AddChunkEntry(this + 0x190, chunkData);
        }

        // Perform any post‑step processing (e.g., align, check CRC)
        PostProcessStep();

        // Recheck stream end condition
        isEnd = IsStreamEndReached();
    }
}