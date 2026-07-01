// FUNC_NAME: PropertyReader::readFromStream
void __thiscall PropertyReader::readFromStream(int thisPtr, int streamPtr)
{
    char hasMore;
    int tag;
    int data;
    
    // Initialize stream reading
    streamBeginRead(streamPtr);
    // Check magic number
    streamReadMagic(streamPtr, 0xbeb24ad4);
    
    hasMore = streamHasMore(streamPtr);
    while (hasMore == 0) {
        // Read next tag
        tag = streamReadTag(streamPtr);
        switch(tag) {
        case 0:
            // Read a boolean flag
            data = streamReadInt(streamPtr);
            if (*(int *)(data + 8) == 0) {
                // Clear bit 0 at offset 0x38
                *(uint32_t *)(thisPtr + 0x38) &= 0xfffffffe;
            } else {
                // Set bit 0 at offset 0x38
                *(uint32_t *)(thisPtr + 0x38) |= 1;
            }
            break;
        case 1:
            // Read a value into offset 0x3c
            data = streamReadInt(streamPtr);
            *(int32_t *)(thisPtr + 0x3c) = *(int32_t *)(data + 8);
            break;
        case 2:
        case 3:
            // Read a value into offset 0x40
            data = streamReadInt(streamPtr);
            *(int32_t *)(thisPtr + 0x40) = *(int32_t *)(data + 8);
            break;
        case 4:
            // Read a value into offset 0x48
            data = streamReadInt(streamPtr);
            *(int32_t *)(thisPtr + 0x48) = *(int32_t *)(data + 8);
            break;
        }
        // Advance to next element
        streamAdvance(streamPtr);
        hasMore = streamHasMore(streamPtr);
    }
    return;
}