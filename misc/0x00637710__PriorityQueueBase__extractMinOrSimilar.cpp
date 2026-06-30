// FUNC_NAME: PriorityQueueBase::extractMinOrSimilar
void __fastcall PriorityQueueBase__extractOrCull(int *pQueue, int *pNodes, int *outIndex)
{
    int *pEnd;
    int minKey;
    int currentKey;
    int mask;
    int index;
    int availableKey;
    int *pKeyIter;

    pEnd = pQueue;
    minKey = *pQueue; // First node key (priority? or size?)
    int currentBestIndex = (minKey != 0) - 1; // init to -1 if minKey==0
    int queueSize = *pNodes; // number of nodes in the node array

    pQueue = (int *)minKey; // reinterpret as current key value

    if (minKey < queueSize) {
        int i = 0;
        pKeyIter = pNodes + 1; // skip first element (size?)
        do {
            mask = 1 << (i & 0x1f); // bit index into mask (1,2,4,...)
            int nodeKey = pEnd[i]; // get key at index i
            if (nodeKey < mask) break; // key not valid, stop
            availableKey = pKeyIter[0]; // get "available" key (maybe threshold?)
            if ((0 < availableKey) && (minKey = minKey + availableKey, mask <= minKey)) {
                // found better candidate
                currentBestIndex = i + 1;
                pQueue = (int *)minKey;
            }
            pKeyIter = pKeyIter + 1;
            i = i + 1;
        } while (minKey < *pEnd);
    }

    *outIndex = pParam1 - (int)pQueue; // offset from current candidate
    if (currentBestIndex != -1) {
        *pEnd = 1 << (currentBestIndex & 0x1f); // update bitmask
        return;
    }
    *pEnd = 0;
    return;
}