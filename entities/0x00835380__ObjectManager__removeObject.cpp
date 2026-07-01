// FUNC_NAME: ObjectManager::removeObject
// Address: 0x00835380
// Role: Removes an object pointer from a dynamic array, shifting remaining elements left.
// Offsets: +0xD0 = array of object pointers, +0xD4 = count of elements
// The object at +0xDC is released before removal.

void __thiscall ObjectManager::removeObject(int thisPtr, int objectPtr)
{
    uint index;
    int* elementPtr;

    // Start from the last index
    index = *(int*)(thisPtr + 0xD4) - 1;
    if ((int)index >= 0)
    {
        elementPtr = (int*)(*(int*)(thisPtr + 0xD0) + index * 4);
        // Search backwards for the matching object pointer
        while (*elementPtr != objectPtr)
        {
            index--;
            elementPtr--;
            if ((int)index < 0)
                return; // Not found
        }
        // Found at index; release sub-object at offset +0xDC
        releaseSubObject(*(int*)(*(int*)(thisPtr + 0xD0) + index * 4) + 0xDC, 0);
        // Shift remaining elements left if not the last
        if (index < *(int*)(thisPtr + 0xD4) - 1U)
        {
            do
            {
                int* current = (int*)(*(int*)(thisPtr + 0xD0) + index * 4);
                *current = *(current + 1);
                index++;
            } while (index < *(int*)(thisPtr + 0xD4) - 1U);
        }
        // Decrement count
        *(int*)(thisPtr + 0xD4) = *(int*)(thisPtr + 0xD4) - 1;
    }
}