// FUNC_NAME: CompactObjectArray::removeAt
void __thiscall CompactObjectArray::removeAt(int* thisPtr, uint index)
{
    // thisPtr[0] = pointer to base of array (each element 12 bytes)
    // thisPtr[1] = element count
    int* arrayBase = (int*)thisPtr[0];
    int count = thisPtr[1];

    // If not removing the last element, shift remaining elements left.
    if (index < count - 1)
    {
        int offset = index * 0xC; // byte offset to element at 'index'
        do
        {
            int* currentNode = (int*)(offset + arrayBase);
            int* nextNode = currentNode + 3; // next element (12 bytes ahead)

            // Always true; likely a compiler artifact
            if (currentNode != nextNode)
            {
                int* objectPtr = nextNode[0]; // pointer stored in next element's first int
                if (currentNode[0] != objectPtr)
                {
                    // If current node has a non-null object, free it first
                    if (currentNode[0] != 0)
                    {
                        FUN_004daf90(currentNode); // destroy object at current node
                    }
                    // Move the object pointer from next node to current
                    currentNode[0] = objectPtr;
                    if (objectPtr != 0)
                    {
                        // Update the back-pointer stored in the object (at +0x04)
                        // to point to the current node instead of the next node
                        currentNode[1] = *(int*)(objectPtr + 4);
                        *(int**)(objectPtr + 4) = currentNode;
                    }
                }
                // Copy the third int (non-pointer data) unconditionally
                currentNode[2] = nextNode[2];
            }
            index++;
            offset += 0xC;
        } while (index < count - 1);
    }

    // Reduce the element count
    thisPtr[1] = count - 1;

    // The last logical element (after decrement) now holds the data that was
    // at the original last position. If it has a non-null object, destroy it.
    int* lastNode = (int*)(arrayBase + thisPtr[1] * 0xC);
    if (lastNode[0] != 0)
    {
        FUN_004daf90(lastNode);
    }
}