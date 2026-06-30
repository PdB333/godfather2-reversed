// FUNC_NAME: LinkedList::extractNodeRange
void LinkedList::extractNodeRange(int *outArray, int *pStart, int *pEnd, int *pBoundStart, int *pBoundEnd)
{
    // +0x1c: pointer to head sentinel node
    // +0x20: list size (set to 0 when emptied)
    int headPrev = **(int **)(this + 0x1c);  // head->prev (self-pointer when empty)

    // pStart and pBoundStart must both be this list (or null)
    if (pStart == 0 || pStart != this) {
        errorHandler();  // FUN_00b97aea
    }
    if (pBoundStart == 0 || pBoundStart != this) {
        errorHandler();
    }

    if (pEnd == headPrev) {
        // The range end is the sentinel head node -> extract entire list
        int *headNode = *(int **)(this + 0x1c);
        removeNode(*(undefined4 *)(headNode + 4));  // FUN_006227f0 – detach head?
        headNode[1] = (int)headNode;                // head->next = head
        *(int *)(this + 0x20) = 0;                  // size = 0
        *headNode = (int)headNode;                  // head->prev = head
        headNode[2] = (int)headNode;                // head->extra = head (maybe padding)
        outArray[1] = **(int **)(this + 0x1c);     // head->prev (now head itself)
        *outArray = (int)this;                      // list object
        return;
    }

    // General case: iterate to validate and find the range
    while (true) {
        if (pStart == 0 || pStart != pBoundStart) {
            errorHandler();
        }
        if (pEnd == pBoundEnd) break;
        // These calls likely traverse or adjust the list
        FUN_006243f0();                          // unknown helper
        FUN_00623a20(this, local_8, pStart, pEnd); // advance nodes, modify local buffer
    }

    outArray[0] = (int)pStart;
    outArray[1] = (int)pEnd;
}