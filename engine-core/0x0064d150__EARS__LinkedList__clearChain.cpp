// FUNC_NAME: EARS::LinkedList::clearChain
// Address: 0x0064d150
// Clears the entire linked list associated with this object.  Sets the vtable pointer, then
// iterates the chain of nodes (starting at offset +0x04) and zeroes each node's three pointer fields.
// Does not deallocate the nodes themselves, only resets their contents.

void __fastcall EARS::LinkedList::clearChain(void* thisPtr)
{
    // +0x00: vtable pointer set to base class vtable (static at 0x00e42de4)
    *(void**)thisPtr = (void*)0x00e42de4;

    // +0x04: head of the linked list (Node*)
    EARS::LinkedListNode* currentNode = *(EARS::LinkedListNode**)((char*)thisPtr + 4);

    while (currentNode != nullptr)
    {
        // +0x08: next node in the list
        EARS::LinkedListNode* nextNode = currentNode->next;

        // Zero all three pointer fields of this node
        currentNode->field0 = nullptr;   // +0x00 (prev or data)
        currentNode->field1 = nullptr;   // +0x04 (data or unused)
        currentNode->next  = nullptr;    // +0x08

        currentNode = nextNode;
    }
}