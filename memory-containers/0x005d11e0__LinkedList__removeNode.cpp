// FUNC_NAME: LinkedList::removeNode
// Function address: 0x005d11e0
// Role: Removes a node from a singly linked list given list and node pointers.
// The list structure has head at +0x0 and tail at +0x4, nodes have next at +0x20.
// After unlinking, calls FUN_005d12b0 which is assumed to free the node.

void __fastcall LinkedList::removeNode(void* listPtr, void* nodePtr) // ECX = nodePtr, EAX = listPtr
{
    if (nodePtr == 0) return;

    // listPtr points to a struct: { void* head; void* tail; }
    void** head = (void**)listPtr;        // +0x0: head of list
    void** tail = (void**)((char*)listPtr + 4); // +0x4: tail of list

    // Node has next pointer at offset 0x20
    void* nextPtr = *(void**)((char*)nodePtr + 0x20);

    // If node is the tail, update tail to its next (which becomes new tail)
    if (*tail == nodePtr)
    {
        *tail = nextPtr;
    }

    // If node is the head, update head to its next
    if (*head == nodePtr)
    {
        *head = nextPtr;
    }

    // Free the node (or perform other cleanup)
    FUN_005d12b0(); // deallocates the node (likely)
}