// FUNC_NAME: IntroSort::introspectiveSortSegment
class SortTable
{
public:
    // Offsets relative to 'this': (vtable at 0x0, not used here)
    int *m_pHead;      // +0x8 : pointer to current head of subarray (may move)
    int *m_pTail;      // +0xC : pointer to sentinel element (type 5) at end of buffer
    // There may be additional fields before +0x8 (e.g., vtable, flags)
};

// External helper functions (renamed based on usage):
void checkSortError(const char *msg);                                           // FUN_00627ac0
int  getSortDepthLimit();                                                       // FUN_00628820(1) – returns max recursion depth
int  getCurrentThreshold();                                                     // FUN_00628080 – returns depth at which to switch to heapsort
void updateDepthCounter(int newDepth);                                         // FUN_006286b0 – sets/stores current depth
int *popHeapRoot();                                                           // FUN_00637f10 – returns pointer to 8-byte pair (key+value) from heap
bool isHeapSentinel(int *ptr);                                                // comparison with DAT_00e2a93c
void pushToHeap(SortTable *buffer, int key, int depth);                        // FUN_00637d60 – insert a pair into heap with depth info
void *allocateNode();                                                          // FUN_00625430 – allocate 8-byte node (for insertion sort)

void SortTable::introspectiveSortSegment()
{
    int *startPtr = m_pHead;
    int *endPtr   = m_pTail;

    // Validate invariants: buffer must be non‑empty and end with type‑5 sentinel
    if ((startPtr <= endPtr) || (endPtr == nullptr) || (*endPtr != 5))
    {
        checkSortError("table");
    }

    // Determine remaining depth limit
    int depthLimit = getSortDepthLimit();   // e.g., 2 * log2(size)
    depthLimit++;

    int elementCount = (startPtr - endPtr) >> 3; // number of 8‑byte elements (negative because start > end)
    int subarraySize = elementCount;               // absolute size

    if (subarraySize == 2)
    {
        // Very small subarray: just insertion sort (swap if needed later)
        // local_18 = 2 indicates insertion‑sort mode
        // iStack_20 = depthLimit (not decremented)
        int swapMode = 2;
        int currentDepth = depthLimit;
    }
    else
    {
        // Larger subarray: check if we should switch to heapsort
        int threshold = getCurrentThreshold();
        int currentDepth = threshold;
        int swapMode = 3; // heapsort mode
        if (depthLimit < currentDepth)
        {
            depthLimit = currentDepth;
        }
        // Update depth counter (possibly decrement for recursion)
        updateDepthCounter(depthLimit);
        // (the original code reuses iVar6 for both depth and loop count)
    }

    // Heapsort phase: repeatedly extract the largest element (root) and sift down
    int heapSize = depthLimit;
    int i = heapSize - 1;
    while (i >= currentDepth)   // currentDepth is either threshold or depthLimit for size==2
    {
        // Save the current element (from the end of the heap) into a temporary node
        int *tempNode = popHeapRoot();
        int *currentPos = m_pHead;

        // Write the temporary node into the current head position
        *currentPos       = tempNode[0];
        *(currentPos + 1) = tempNode[1];
        m_pHead += 8; // advance head

        // Now get the next root from the heap (largest remaining)
        int *nextRoot = popHeapRoot();
        if (isHeapSentinel(nextRoot))
        {
            // Sentinel encountered: we need to reinsert the saved element with depth info
            int savedKey = *(int *)(*(m_pTail) + 4); // the second int of the sentinel (some key)
            int depthInfo[2] = { 3, 0 };            // local_18 is stored here? Actually uStack_10 = 3
            pushToHeap(this, savedKey, depthInfo);
        }

        // Write back the saved node into the position just before the current head
        int *prevHead = m_pHead - 8;
        *nextRoot       = *prevHead;
        *(nextRoot + 1) = *(prevHead + 1);
        m_pHead -= 8; // move head back
        i--;
        heapSize--;
    }

    // Final step: decide how to place the last remaining element
    int *finalSource;
    if (swapMode == 0) // never happens due to logic
    {
        finalSource = (int *)allocateNode();
    }
    else
    {
        // In insertion‑sort mode (swapMode == 2), the last element is at position
        // m_pTail - 8 + 2*8 = m_pTail + 8 (since subarray size was 2)
        // In heapsort mode, it's also computed similarly: m_pTail - 8 + swapMode*8
        finalSource = m_pTail - 8 + swapMode * 8;
    }

    // Write the final element into current head position
    int *dest = m_pHead;
    *dest       = *finalSource;
    *(dest + 1) = *(finalSource + 1);
    m_pHead += 8;

    // One more adjustment: the sentinel's key is needed
    int sentinelKey = *(int *)(*m_pTail + 4); // second int of sentinel
    int *prevPos = m_pHead - 8;
    int *nextRoot = popHeapRoot();
    if (isHeapSentinel(nextRoot))
    {
        float depthAsFloat = (float)currentDepth;
        int depthInfo[2] = { 3, 0 };
        pushToHeap(this, sentinelKey, depthInfo);
    }

    // Overwrite the previously saved element with the sentinel position
    *nextRoot       = *prevPos;
    *(nextRoot + 1) = *(prevPos + 1);
    m_pHead -= 8;

    return;
}