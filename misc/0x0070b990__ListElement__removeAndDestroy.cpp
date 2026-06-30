// FUNC_NAME: ListElement::removeAndDestroy
// Address: 0x0070b990
// Removes this element from a doubly-linked list, calls base destructor, optionally frees memory

int __thiscall ListElement::removeAndDestroy(int this, byte flags)
{
    // Set virtual table pointer at offset +0x28
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;

    // List structure offsets:
    // +0x18 = pointer to previous element (pPrev)
    // +0x1c = pointer to next element (pNext)
    // +0x20 = pointer to associated data block (pData)
    // The associated data block has its own list pointers at +0x04 and +0x08
    // (likely pData->pPrevUnk at +0x04, pData->pNextUnk at +0x08)

    int* pPrev = *(int**)(this + 0x18);
    if (pPrev != 0)
    {
        int* pNext = *(int**)(this + 0x1c);
        int* pData = *(int**)(this + 0x20);

        if (pNext == 0)
        {
            // No next element: set prev->pNextUnk = this->pData
            *(int*)(pPrev + 1) = (int)pData;   // pPrev+4 = pData
        }
        else
        {
            // Has next element: set next->pPrevUnk = this->pData
            *(int*)(pNext + 2) = (int)pData;   // pNext+8 = pData
        }

        if (pData != 0)
        {
            // Set pData->pPrevUnk = this->pNext
            *(int*)(pData + 1) = (int)pNext;   // pData+4 = pNext
        }
    }

    // Call base destructor (likely cleans up owned resources)
    FUN_0064d150();

    // If flag bit 0 set, deallocate memory
    if ((flags & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return this;
}