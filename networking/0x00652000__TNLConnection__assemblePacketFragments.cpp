// FUNC_NAME: TNLConnection::assemblePacketFragments

// Function at 0x00652000: Reassembles packet data from an internal buffer of paired fragments.
// This member function processes a circular buffer of packet chunks, interleaving pairs
// and copying the remainder when the buffer is not fully paired.
// Parameters:
//   fragmentSequence - upper 24 bits used as a sequence/flag indicator (lower 8 bits masked out)
//   srcEnd - pointer to the end of the internal buffer (cast to int for difference calculation)
//   destBuffer - output buffer for reassembled data
//   chunkSizeWords - size of each fragment chunk in 32-bit words
//   totalWordsRemaining - total number of 32-bit words still to be processed
//   flags - additional control flags passed to the chunk processing routine

void __thiscall TNLConnection::assemblePacketFragments(
    uint fragmentSequence,
    int srcEnd,
    void *destBuffer,
    uint chunkSizeWords,
    int totalWordsRemaining,
    undefined4 flags)
{
    void *nextChunkStart;           // pvVar1
    rsize_t copySize;               // _DstSize
    uint currentChunkSize;          // uVar2
    void *currentBufferPos;         // _Src (in_EAX = this)
    int residueWordCount;           // iVar3
    void *bufferStart;              // in_EAX (this)

    currentChunkSize = chunkSizeWords;
    uint seqMasked = fragmentSequence & 0xffffff00; // Preserve only the upper 24 bits

    bufferStart = this; // implicit this pointer passed via EAX

    // Process pairs of chunks while at least two chunks remain
    while ((int)(chunkSizeWords * 2) <= totalWordsRemaining)
    {
        // Load the start of the second chunk in the current pair
        nextChunkStart = (void *)((int)bufferStart + chunkSizeWords * 4);
        // Load the start of the next pair (end of the second chunk)
        currentBufferPos = (void *)((int)nextChunkStart + chunkSizeWords * 4);

        // Call the interleaving routine with: second chunk, end of pair, destination, flags, chunk size, masked sequence
        FUN_00652520(nextChunkStart, currentBufferPos, destBuffer, flags, chunkSizeWords, seqMasked);

        // Advance the destination pointer by the total amount of data produced (two chunks)
        int bytesProduced = ((int)currentBufferPos - (int)nextChunkStart) / 4;  // = chunkSizeWords
        bytesProduced += ((int)nextChunkStart - (int)bufferStart) / 4;        // = chunkSizeWords
        destBuffer = (void *)((int)destBuffer + bytesProduced * 4);           // 2 * chunkSizeWords * 4 bytes

        // Decrease the remaining count by two chunks
        totalWordsRemaining -= chunkSizeWords * 2;

        // Advance the internal buffer position to the start of the next pair
        bufferStart = currentBufferPos;
    }

    // Handle the last incomplete pair (one chunk remaining)
    if ((int)chunkSizeWords < totalWordsRemaining)
    {
        // Mask chunk size to multiples of 256 (lower 8 bits cleared)
        chunkSizeWords = chunkSizeWords & 0xffffff00;
        // The second source is the original srcEnd pointer (external buffer)
        FUN_00652520((void *)((int)currentBufferPos + currentChunkSize * 4), srcEnd, destBuffer, flags, chunkSizeWords, chunkSizeWords);
    }
    else
    {
        // No complete chunk left; copy the remaining raw data directly
        residueWordCount = (srcEnd - (int)currentBufferPos) / 4;
        if (0 < residueWordCount)
        {
            copySize = residueWordCount * 4;
            _memmove_s(destBuffer, copySize, currentBufferPos, copySize);
        }
    }
    return;
}