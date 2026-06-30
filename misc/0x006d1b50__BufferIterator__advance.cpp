// FUNC_NAME: BufferIterator::advance

bool __fastcall BufferIterator::advance(char *thisPtr)
{
    // Offset 0x04: collection identifier (handle or ID)
    // Offset 0x08: current index
    // Offset 0x0C: first index (used to detect wrap-around)
    // Offset 0x10: pointer to element buffer (array of indices or objects)
    // Offset 0x00: initialization flag (0 = first call, 1 = subsequent)

    int collectionState = getCollectionState(*(int *)(thisPtr + 0x04));
    if (collectionState == 4)
    {
        // Collection is full or exhausted
        return false;
    }

    if (thisPtr[0] == 0)
    {
        // First time: get the starting index from the collection
        int startIndex = getNextIndex(*(int *)(thisPtr + 0x04), thisPtr + 0x10, 0);
        *(int *)(thisPtr + 0x08) = startIndex;
        *(int *)(thisPtr + 0x0C) = startIndex;
        thisPtr[0] = 1;
        return true;
    }
    else
    {
        // Subsequent calls: advance to next index
        int nextIndex = getNextIndex(*(int *)(thisPtr + 0x04), thisPtr + 0x10, *(int *)(thisPtr + 0x08));
        *(int *)(thisPtr + 0x08) = nextIndex;
        // Returns true until we wrap back to the first index
        return *(int *)(thisPtr + 0x0C) != nextIndex;
    }
}