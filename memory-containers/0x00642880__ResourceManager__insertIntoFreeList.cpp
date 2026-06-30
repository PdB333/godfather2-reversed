// FUNC_NAME: ResourceManager::insertIntoFreeList
// Address: 0x00642880
// Role: Inserts a resource ID into a free list / hash chain. The 'headPtr' points to the head of a linked list of indices.
// The table at param3+0x0c stores 'next' indices encoded as (value >> 6) & 0x3FFFF. 
// If the slot's next value equals 0x1FFFE (FREE_SENTINEL), the list is considered full/broken and an error handler is called.

void __fastcall ResourceManager::insertIntoFreeList(int newId, int* headPtr, int* tableBase)
{
    // newId is passed in EAX (not a standard parameter), must be != -1 to proceed.
    if (newId == -1) {
        return;
    }

    int nodeIndex = *headPtr;
    if (nodeIndex == -1) {
        // Empty list -> insert as first element
        *headPtr = newId;
        return;
    }

    // Follow the chain using the 'next' field from the table at tableBase+0x0c
    do {
        // Extract next index from table entry: (entry >> 6) & 0x3FFFF
        int entry = *(int*)(*(int*)(tableBase + 0xc) + nodeIndex * 4); // tableBase+0x0c is a pointer to array
        int nextIndex = (entry >> 6) & 0x3FFFF;

        if (nextIndex == 0x1FFFE) {
            // Sentinel: end of free chain reached without finding a free slot
            break;
        }

        nodeIndex = (nextIndex - 0x1FFFE) + nodeIndex; // This computes new node index
    } while (nodeIndex != -1);

    // If we broke out due to sentinel, call error handler (likely prints error or asserts)
    ResourceManager::handleFreeListError(); // FUN_00642550
    return;
}