// FUNC_NAME: GameObject::~GameObject
void __thiscall GameObject::destructor(GameObject* this)
{
    uint i;
    GameObject* childPtr;
    int childIndex;

    // Set vtable to this class's vtable
    this->vtable = &PTR_FUN_00e35378;

    // Call base class destructor (or common cleanup)
    FUN_004a6460(0, 0);

    // Release all children in childrenArray (pointers at +0x5C, count at +0x60)
    for (i = 0; i < this->childrenCount; i++)
    {
        childPtr = this->childrenArray[i];
        if (childPtr)
        {
            // Call first virtual function (release) with argument 1
            childPtr->vtable[0](1);
        }
    }

    // Release all children in otherChildrenArray (array of 16-byte structs at +0x68, count at +0x6C)
    for (i = 0; i < this->otherChildrenCount; i++)
    {
        childPtr = *(GameObject**)(this->otherChildrenArray + i * 16);
        if (childPtr)
        {
            childPtr->vtable[0](1);
        }
    }

    // Remove node at +0x94 (external list node) from its doubly linked list
    if (this->externalListNode)
    {
        // Node structure: +0x00 = data?, +0x04 = prev, +0x08 = next
        // Unlink from list
        if (this->externalListNode->prev)
        {
            this->externalListNode->prev->next = this->externalListNode->next;
        }
        if (this->externalListNode->next)
        {
            this->externalListNode->next->prev = this->externalListNode->prev;
        }
        // Update global list head/tail
        if (g_externalListHead == this->externalListNode)
        {
            g_externalListHead = this->externalListNode->next;
        }
        if (g_externalListTail == this->externalListNode)
        {
            g_externalListTail = this->externalListNode->prev;
        }
        // Clear node pointers
        this->externalListNode->next = nullptr;
        this->externalListNode->prev = nullptr;
        // Free the node memory
        FUN_009c8eb0(this->externalListNode);
    }

    // Free allocated string at +0x04
    FUN_009c8eb0(this->name);

    // Remove this object from list A (pointers at +0x84 and +0x88)
    if (this->listAPrev)
    {
        this->listAPrev->listANext = this->listANext;
    }
    if (this->listANext)
    {
        this->listANext->listAPrev = this->listAPrev;
    }
    if (g_listAHead == this)
    {
        g_listAHead = this->listANext;
    }
    if (g_listATail == this)
    {
        g_listATail = this->listAPrev;
    }
    this->listANext = nullptr;
    this->listAPrev = nullptr;

    // Remove this object from list B (pointers at +0x8C and +0x90)
    if (this->listBPrev)
    {
        this->listBPrev->listBNext = this->listBNext;
    }
    if (this->listBNext)
    {
        this->listBNext->listBPrev = this->listBPrev;
    }
    if (g_listBHead == this)
    {
        g_listBHead = this->listBNext;
    }
    if (g_listBTail == this)
    {
        g_listBTail = this->listBPrev;
    }
    this->listBNext = nullptr;
    this->listBPrev = nullptr;

    // Free various allocated memory blocks
    if (this->someAllocation1)
    {
        FUN_009c8f10(this->someAllocation1);
    }
    if (this->otherChildrenArray)
    {
        FUN_009c8f10(this->otherChildrenArray);
    }
    if (this->childrenArray)
    {
        FUN_009c8f10(this->childrenArray);
    }
    if (this->someAllocation2)
    {
        FUN_009c8f10(this->someAllocation2);
    }

    // Set vtable to base class vtable (prevents virtual calls during further destruction)
    this->vtable = &PTR_LAB_00e2f638;
}