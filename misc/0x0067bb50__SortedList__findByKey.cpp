// FUNC_NAME: SortedList::findByKey
uint __thiscall SortedList::findByKey(void *this, ushort searchKey, ushort *outIndex)
{
    int *arrayPtr;
    ushort currentKey;
    bool bVar;
    int low;
    int high;
    int mid;

    low = 0;
    // +0x108 holds the count (as short)
    high = *(short *)((int)this + 0x108) - 1;
    if (high >= 0) {
        // +0x0C holds a pointer to the array of 8-byte elements
        arrayPtr = *(int **)((int)this + 0x0C);
        do {
            mid = (low + high) / 2;
            currentKey = *(ushort *)((int)arrayPtr + mid * 8);
            if (searchKey == currentKey) {
                bVar = false;
LAB_0067bb76:
                low = mid + 1;
                if (!bVar) {
                    // Found: write index to output pointer
                    *outIndex = (ushort)mid;
                    // Return 1 in low byte, index shifted left 8 bits (but index is small so high bits are zero)
                    return (uint)((mid >> 8) & 0xFFFFFF) << 8 | 1;
                }
            } else {
                if (currentKey <= searchKey) {
                    bVar = true;
                    goto LAB_0067bb76;
                }
                high = mid - 1;
            }
        } while (low <= high);
    }
    // Not found: return index in upper bits (low byte 0)
    return (uint)((mid >> 8) & 0xFFFFFF) << 8; // Actually returns in_EAX & 0xFFFFFF00, which clears low byte; mid is last probe
}