// FUNC_004de130: SimObject::~SimObject

void __thiscall SimObject::~SimObject(SimObject *this)
{
    SimObject *pNext;
    SimObject *pCurrent;
    SimObject *pGlobalIter;
    SimObject *pGlobalPrev;
    SimObject *pInternalHead;

    // Set vtable to derived class vtable (placeholder)
    // +0x00: vtable pointer
    this->vtable = &PTR_FUN_00e36f14;

    // Internal linked list head stored at offset 0x30 (12 dwords)
    pInternalHead = *(SimObject **)((char *)this + 0x30); // +0x30

    // Global list head (static)
    pGlobalPrev = g_pObjectListHead; // DAT_012054b8

    // Delete all nodes in internal list
    while (g_pObjectListHead = pGlobalPrev, pInternalHead != NULL)
    {
        pNext = *(SimObject **)((char *)pInternalHead + 4); // +0x04: next pointer
        freeNode(pInternalHead); // FUN_009c8eb0
        pInternalHead = pNext;
        pGlobalPrev = g_pObjectListHead;
    }

    // Switch to base class vtable
    // +0x00: vtable pointer
    this->vtable = &PTR_LAB_00e36f0c;

    // Unlink this object from global list
    if (pGlobalPrev != this)
    {
        // Find the node that points to this
        pGlobalIter = (SimObject *)pGlobalPrev->next; // +0x04
        while (pGlobalIter != this)
        {
            pGlobalPrev = (SimObject *)pGlobalPrev->next; // +0x04
            pGlobalIter = (SimObject *)pGlobalPrev->next; // +0x04
        }
        // Remove this from list: previous node's next = this's next
        pGlobalPrev->next = this->next; // +0x04
    }
    else
    {
        // This is the head of global list, update head
        g_pObjectListHead = (SimObject *)this->next; // +0x04
    }
}