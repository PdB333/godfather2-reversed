// FUNC_NAME: SlotArray::removeElement
void __fastcall SlotArray::removeElement(int thisPtr, int elementPtr)
{
    // +0x200: mCount (number of active elements)
    int* mCount = (int*)(thisPtr + 0x200);
    // +0x1fc: mpElements (pointer to array of element pointers)
    int** mpElements = (int**)(*(int*)(thisPtr + 0x1fc));
    // +0x2c: element's index in array
    int* elementIndex = (int*)(elementPtr + 0x2c);

    // Decrement element count
    *mCount = *mCount - 1;

    // If the removed element is not the last one, swap it with the last element
    if (*elementIndex != *mCount)
    {
        // Move last element's index to the slot being freed
        *(int*)(mpElements[*mCount] + 0x2c) = *elementIndex;
        // Copy the last element pointer into the freed slot
        mpElements[*elementIndex] = mpElements[*mCount];
        // Place the removed element at the now-empty last slot
        mpElements[*mCount] = (int*)elementPtr;
        // Update the removed element's index to the new last slot
        *elementIndex = *mCount;
    }
    // If removing the last element, only the count decrement is needed
}