// FUNC_NAME: IntrusiveList::initializeNode
void __thiscall IntrusiveList::initializeNode(void* thisPtr, void* listContainer) // thisPtr is in EAX, listContainer in ESI (custom convention)
{
    // thisPtr: pointer to a node that has a vtable pointer at offset 0 and a reference or data at offset 4
    // listContainer: pointer to the list struct that holds the sentinel node pointer at +0x1c and count at +0x20

    // Get vtable from thisPtr
    void** vtable = *(void***)thisPtr; // *in_EAX
    int dataField = *(int*)(thisPtr + 4); // in_EAX[1]

    // Call virtual function at vtable+8 (likely release/cleanup)
    ((void (__thiscall*)(void*))vtable[2])(thisPtr);

    // Process data field: if non-zero, call a conversion function
    int convertedData;
    if (dataField == 0) {
        convertedData = 0;
    } else {
        convertedData = FUN_004265d0(dataField, thisPtr); // likely a resource or pointer conversion
    }

    // Insert the node into the list managed by listContainer
    FUN_00622f60(listContainer, thisPtr, convertedData);

    // Allocate a new sentinel node for the list
    int* sentinelNode = (int*)FUN_00623880(); // allocate memory
    *(int**)(listContainer + 0x1c) = sentinelNode; // store sentinel at +0x1c

    // Initialize sentinel node structure
    *(char*)(sentinelNode + 0x25) = 1; // set flags byte at offset 0x25
    sentinelNode[1] = (int)sentinelNode; // sentinel->next = sentinel  (+4)
    *(int*)sentinelNode = (int)sentinelNode; // sentinel->prev = sentinel  (+0)
    sentinelNode[2] = (int)sentinelNode; // sentinel->someThird = sentinel  (+8)  // possibly tail or something

    // Reset count or pointer at +0x20
    *(int*)(listContainer + 0x20) = 0;
}