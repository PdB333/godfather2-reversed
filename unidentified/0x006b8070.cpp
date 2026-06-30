// FUN_NAME: readDataRecordFromStream
// Address: 0x006b8070
// Reads typed entries from a stream and fills an output array of 9 values (types 0..8).
// param_1 is output array of 9 uint32s; param_2 is stream handle.
void __thiscall readDataRecordFromStream(uint32_t* outArray, uint32_t streamHandle)
{
    char hasMore;
    uint32_t entryType;
    int32_t dataPtr;

    // Begin reading stream with a magic/hash constant
    beginRead(streamHandle, 0x9c61ae2c);

    hasMore = isEnd();  // Returns non-zero when stream is exhausted?
    while (hasMore == '\0') {
        // Advance to next entry
        advanceToNext();

        // Get the type of the current entry
        entryType = getEntryType();

        switch (entryType) {
        case 0:
            dataPtr = advanceToNext();  // Gets pointer to data element
            outArray[0] = *(uint32_t*)(dataPtr + 8);
            break;
        case 1:
            dataPtr = advanceToNext();
            outArray[1] = *(uint32_t*)(dataPtr + 8);
            break;
        case 2:
            dataPtr = advanceToNext();
            outArray[2] = *(uint32_t*)(dataPtr + 8);
            break;
        case 3:
            dataPtr = advanceToNext();
            outArray[3] = *(uint32_t*)(dataPtr + 8);
            break;
        case 4:
            dataPtr = advanceToNext();
            outArray[4] = *(uint32_t*)(dataPtr + 8);
            break;
        case 5:
            dataPtr = advanceToNext();
            outArray[5] = *(uint32_t*)(dataPtr + 8);
            break;
        case 6:
            dataPtr = advanceToNext();
            outArray[6] = *(uint32_t*)(dataPtr + 8);
            break;
        case 7:
            dataPtr = advanceToNext();
            outArray[7] = *(uint32_t*)(dataPtr + 8);
            break;
        case 8:
            dataPtr = advanceToNext();
            outArray[8] = *(uint32_t*)(dataPtr + 8);
            break;
        }

        // Call some kind of finalizer or next step
        finalizeEntry();

        hasMore = isEnd();
    }
    return;
}