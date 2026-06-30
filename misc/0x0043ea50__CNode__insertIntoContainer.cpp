// FUNC_NAME: CNode::insertIntoContainer
CNode* CNode::insertIntoContainer(CContainer* container)
{
    // this is the node being inserted
    vtable_t* vtable = *(vtable_t**)this; // pointer to vtable
    int childPtr = *(int*)((char*)this + 4); // offset +0x04: child object pointer or 0

    // Call virtual function at vtable offset 0x08 (likely InitializeChild or similar)
    (*(void(__thiscall**)(CNode*))(vtable->funcPtrArray[2]))(this);

    // If child pointer exists, process it
    int processedChild = 0;
    if (childPtr != 0)
    {
        processedChild = FUN_004265d0(childPtr, vtable); // unknown helper: processes child
    }

    // Link this node into the container's list
    FUN_0043f0c0(container, vtable, processedChild); // unknown linker function

    // Retrieve container's head pointer (offset +0x04 from container)
    CNode** headPtr = (CNode**)((char*)container + 4);
    CNode* headNode = *headPtr;
    CNode dummyStackNode; // fallback if head is null
    if (headNode == nullptr)
    {
        // Use dummy on stack to avoid null pointer
        headNode = &dummyStackNode;
        dummyStackNode.next = nullptr;
        dummyStackNode.prev = nullptr;
    }

    // Allocate a new node of size 0xC via container's allocator (virtual function at offset 0)
    CNodeAllocator allocFunc = (CNodeAllocator)(*(void***)container)[0];
    CNode* newNode = (CNode*)allocFunc(0xC, headNode); // allocate new node

    // Initialize new node as a doubly linked list node (self-referencing)
    if (newNode != nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
    }

    // Store new node as container's head (offset +0x18) and clear count (offset +0x1C)
    *(CNode**)((char*)container + 0x18) = newNode;
    *(int*)((char*)container + 0x1C) = 0;

    return container;
}