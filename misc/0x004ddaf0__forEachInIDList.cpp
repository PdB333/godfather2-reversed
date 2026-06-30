// FUNC_NAME: forEachInIDList
// Address: 0x004DDAF0
// Role: Iterates over a zero-terminated list of short IDs (or indices) and calls a handler function with each ID and a context parameter.
// This is a helper function used by multiple callers to apply some operation (FUN_004DDA40) to every element in a short array.

// Note: The handler FUN_004DDA40 is the actual processing per element.

void forEachInIDList(short *idList, uint32_t contextParam)
{
    short currentId = *idList;

    while (currentId != 0) {
        // Call the per-element handler
        FUN_004DDA40(currentId, contextParam);

        // Advance to next element
        idList++;
        currentId = *idList;
    }
}