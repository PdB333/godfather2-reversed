// FUNC_NAME: ListManager::destroyAllNodes
void __fastcall ListManager::destroyAllNodes(void* thisPtr)
{
    // thisPtr is the manager object
    // +0x18: pointer to sentinel node (circular doubly-linked list)
    Node* sentinel = *(Node**)((char*)thisPtr + 0x18);
    Node* currNode = *sentinel; // first node (sentinel->next)
    
    // Initialize sentinel to point to itself (empty list) as we iterate
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    
    // Reset count (offset +0x1C)
    *(int*)((char*)thisPtr + 0x1C) = 0;
    
    if (currNode != sentinel)
    {
        do
        {
            short refCount = *(short*)((char*)currNode + 0x1A);
            Node* nextNode = currNode->next; // save next before modification
            
            // Overwrite vtable pointer with a fixed destructor table
            currNode->vtable = (void*)&PTR_FUN_00d6ffac;
            
            // Decrement reference count until zero (FUN_00408090 likely releases one reference)
            while (refCount != 0)
            {
                FUN_00408090(); // releaseReference or similar
                refCount = *(short*)((char*)currNode + 0x1A);
            }
            
            // If attached object exists and destruction flag not set (bit 0 of byte at +0x20)
            if (currNode->attachedObject != nullptr && ((*(unsigned char*)(currNode + 8) & 1) == 0))
            {
                // Call the first virtual function on the attached object with argument 1
                (*(void(__thiscall**)(void*, int))currNode->attachedObject->vtable)(currNode->attachedObject, 1);
            }
            
            // Call the manager's second virtual function (likely nodeDestructor) on the node with size 0x24
            (*(void(__thiscall**)(void*, Node*, int))thisPtr->vtable + 4)(thisPtr, currNode, 0x24);
            
            currNode = nextNode;
        } while (nextNode != sentinel);
    }
}