// FUNC_NAME: ResourceTable::findEntryByKey

undefined4 __thiscall ResourceTable::findEntryByKey(int thisPtr, int *key, uint *outIndex, undefined4 *outHandle)
{
    undefined4 result = 0;
    uint i = 0;
    
    if (*(uint *)(thisPtr + 0xa4) != 0) {
        int *entryPtr = *(int **)(thisPtr + 0xa0);
        int *keyComparisonBase = entryPtr + 4; // +4 ints from entry start
        
        while (
            ((*entryPtr == 0 || *entryPtr == 0x48) || // skip empty/invalid entries
             (keyComparisonBase[-2] != *key)) ||      // key[0] mismatch
            ((keyComparisonBase[-1] != key[1]) ||     // key[1] mismatch
             (*keyComparisonBase != key[2]) ||        // key[2] mismatch
             (keyComparisonBase[1] != key[3]))        // key[3] mismatch
            )
        {
            i++;
            entryPtr += 6;        // next entry (6 ints = 24 bytes)
            keyComparisonBase += 6;
            if (*(uint *)(thisPtr + 0xa4) <= i) {
                return result;    // not found
            }
        }
        
        *outIndex = i;                               // found index
        result = getHandleFromEntry();               // always called after match
        *outHandle = result;
        result = 1;
    }
    
    return result;
}