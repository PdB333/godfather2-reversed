// FUNC_NAME: CircularBufferMatcher::findCircularMatchIndex
// Function address: 0x00824620
// Searches for a circular pair of consecutive nodes (wrapping around) where the comparison function returns non-zero.
// Returns the index of the first node in the pair, or -1 (0xFFFFFFFF) if none found.

uint __thiscall findCircularMatchIndex(void* this, uint someData)
{
    int count = *(int*)((int)this + 0xC); // +0xC : mCount (number of nodes)
    if (count == 0) {
        return 0xFFFFFFFF;
    }
    if (count == 1) {
        return 0;
    }

    uint currentIndex = *(uint*)((int)this + 0x4); // +0x4 : mCurrentIndex
    int nextIndex;
    if (currentIndex < count - 1) {
        nextIndex = currentIndex + 1;
    } else {
        nextIndex = 0;
    }

    // Compare the pair starting at currentIndex
    char cmpResult = FUN_00821840(
        someData,
        *(int*)(*(int*)((int)this + 0x8) + currentIndex * 4) + 4, // +0x8 : mArray (array of pointers)
        *(int*)(*(int*)((int)this + 0x8) + nextIndex * 4) + 4
    );
    if (cmpResult != 0) {
        return *(uint*)((int)this + 0x4); // return mCurrentIndex
    }

    // Linear scan over all cyclic pairs starting from 0
    uint numPairs = *(uint*)((int)this + 0xC);
    uint i = 0;
    if (numPairs != 0) {
        do {
            if (i < numPairs - 1) {
                nextIndex = i + 1;
            } else {
                nextIndex = 0;
            }
            cmpResult = FUN_00821840(
                someData,
                *(int*)(*(int*)((int)this + 0x8) + i * 4) + 4,
                *(int*)(*(int*)((int)this + 0x8) + nextIndex * 4) + 4
            );
            if (cmpResult != 0) {
                return i;
            }
            numPairs = *(uint*)((int)this + 0xC);
            i++;
        } while (i < numPairs);
    }

    return 0xFFFFFFFF;
}