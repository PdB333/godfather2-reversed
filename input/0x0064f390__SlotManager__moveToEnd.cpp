// FUNC_NAME: SlotManager::moveToEnd
void __fastcall SlotManager::moveToEnd(SlotManager* this, void* element)
{
    // this+0x204: m_lastIndex (int) - index of the last occupied slot
    // this+0x1fc: m_items (void**) - array of pointers to elements
    // element+0x2c: m_index (int) - current index of the element

    int lastIndex = this->m_lastIndex - 1;  // decrement to get the new last index
    this->m_lastIndex = lastIndex;

    if (*(int*)((char*)element + 0x2c) != lastIndex)
    {
        // Move the element currently at lastIndex into the slot of the element being moved
        void* lastElement = this->m_items[lastIndex];
        *(int*)((char*)lastElement + 0x2c) = *(int*)((char*)element + 0x2c);  // update its index
        this->m_items[*(int*)((char*)element + 0x2c)] = lastElement;          // swap pointers

        // Place the element at the last index
        this->m_items[lastIndex] = element;
        *(int*)((char*)element + 0x2c) = lastIndex;  // update element's index
    }
}