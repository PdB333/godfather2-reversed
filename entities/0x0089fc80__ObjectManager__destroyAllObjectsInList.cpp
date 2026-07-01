// FUNC_NAME: ObjectManager::destroyAllObjectsInList
// Address: 0x0089fc80
// Role: Iterates over a doubly linked list of objects, calls a virtual release method on each (vtable at offset -0x1c from object pointer), clears the list, then deallocates a member pointer at this+0xb4.

void __thiscall ObjectManager::destroyAllObjectsInList(LinkedListNode* listHead)
{
    // Iterate over the doubly linked list with sentinel head
    LinkedListNode* node = listHead->next;
    while (node != listHead)
    {
        LinkedListNode* nextNode = node->next; // save next before potential modification

        // node->objectPtr is at offset +0x08 in the node structure.
        // It can be 0, 0x1c (sentinel), or a valid pointer to an object.
        uint32_t objectPtr = node->objectPtr;
        if (objectPtr != 0 && objectPtr != 0x1c && objectPtr != 0)
        {
            // The object's vtable is located at (objectPtr - 0x1c).
            // This is a common pattern where the allocation header precedes the user pointer.
            void** vtable = (void**)(objectPtr - 0x1c);
            // Call the first virtual function (typically a release/destructor) with argument 1.
            typedef void (*ReleaseFunc)(int);
            ReleaseFunc release = (ReleaseFunc)(*vtable);
            release(1);
        }

        node = nextNode;
    }

    // Global cleanup (likely memory manager or debug logging)
    GlobalCleanup(); // FUN_0089ed40

    // Reset the list to empty (sentinel points to itself)
    listHead->next = listHead;
    listHead->prev = listHead;

    // Deallocate the member pointer at this+0xb4 if it exists
    if (this->somePointer != 0)
    {
        MemoryDeallocate(this->somePointer); // FUN_004daf90
        this->somePointer = 0;
    }
}

// Node structure for the doubly linked list
struct LinkedListNode
{
    LinkedListNode* next;   // +0x00
    LinkedListNode* prev;   // +0x04
    uint32_t objectPtr;     // +0x08 (pointer to object or sentinel 0x1c)
};