// FUNC_NAME: SlotArray::setSize
void __thiscall SlotArray::setSize(int newSize)
{
    int oldSize = this->mSize;

    if (newSize > oldSize)
    {
        FUN_004b1440(newSize); // realloc/grow the slot array
        oldSize = this->mSize;

        if (oldSize < newSize)
        {
            // Initialize newly allocated slots to zero
            Slot* slots = this->mSlots;
            for (int i = oldSize; i < newSize; i++)
            {
                slots[i].node = nullptr;   // +0x00
                slots[i].next = nullptr;   // +0x04
            }
            this->mSize = newSize;
            return;
        }
    }
    else if (newSize < oldSize)
    {
        // Shrink: remove slots from newSize to oldSize-1
        Slot* slots = this->mSlots;
        for (int i = oldSize - 1; i >= newSize; i--)
        {
            void* node = slots[i].node; // first field of slot
            if (node != nullptr)
            {
                void** backPtr = (void**)((char*)node + 4); // node's +0x04 (back pointer)
                void* back = *backPtr;

                if (back == &slots[i]) // node points directly to this slot
                {
                    *backPtr = slots[i].next; // slot's second field
                }
                else
                {
                    // Walk the list to find the node whose back pointer points to this slot
                    void* prev = back;
                    void* cur = *(void**)((char*)prev + 4); // node after prev
                    while (cur != &slots[i])
                    {
                        prev = *(void**)((char*)prev + 4);
                        cur = *(void**)((char*)prev + 4);
                    }
                    *(void**)((char*)prev + 4) = slots[i].next;
                }
            }
        }
        this->mSize = newSize;
    }
    // else equal: nothing
}