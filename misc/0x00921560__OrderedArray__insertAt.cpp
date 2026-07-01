// FUNC_NAME: OrderedArray::insertAt
// Function address: 0x00921560
// Role: Inserts a new empty node at the specified index in an ordered array that also maintains a linked list of nodes.
// The array stores nodes of 8 bytes each: first 4 bytes are a pointer to some object (data), second 4 bytes are a pointer to the next node in the linked list.
// The linked list order mirrors the array order (insertion order). When inserting not at the end, existing nodes are shifted right and their linked list pointers are updated.

int __thiscall OrderedArray::insertAt(int* thisPtr, uint index)
{
    int* nodePtr;
    uint currentCount;
    int capacity;
    int* prevNodeData;
    int* shiftedNode;
    int* newSlot;

    capacity = thisPtr[2]; // +0x08: capacity
    if (thisPtr[1] == capacity) // +0x04: current count
    {
        if (capacity == 0)
        {
            capacity = 1;
        }
        else
        {
            capacity = capacity * 2;
        }
        // Reallocate the array to new capacity (function at 0x00920c00)
        FUN_00920c00(capacity);
    }

    // Pointer to the new slot at the end of the array (before potential shift)
    nodePtr = (int*)(*thisPtr + thisPtr[1] * 8); // +0x00: base pointer

    if (index != thisPtr[1])
    {
        // Inserting not at the end: need to shift elements and update linked list
        if (nodePtr != (int*)0x0)
        {
            // Get the data pointer from the previous node (the one before the new slot)
            prevNodeData = (int*)nodePtr[-2]; // nodePtr[-2] is the first field of the previous node (at count-1)
            // Set new node's data pointer to that
            *nodePtr = (int)prevNodeData;
            nodePtr[1] = 0; // Initialize next pointer to null
            if (prevNodeData != (int*)0x0)
            {
                // Insert new node after the previous node in the linked list
                nodePtr[1] = *(int*)((int)prevNodeData + 4); // new node's next = previous node's next
                *(int**)((int)prevNodeData + 4) = nodePtr;   // previous node's next = new node
            }
        }

        // Shift elements from the end down to the insertion point
        currentCount = thisPtr[1];
        while (currentCount = currentCount - 1, index < currentCount)
        {
            shiftedNode = (int*)(*thisPtr + currentCount * 8);
            // shiftedNode[-2] is the first field of the node before shiftedNode
            prevNodeData = (int*)shiftedNode[-2];
            if (*shiftedNode != (int)prevNodeData)
            {
                if (*shiftedNode != 0)
                {
                    // Release the old data pointer (function at 0x004daf90)
                    FUN_004daf90(shiftedNode);
                }
                // Update shifted node's data pointer to the previous node's data
                *shiftedNode = (int)prevNodeData;
                if (prevNodeData != (int*)0x0)
                {
                    // Update linked list pointers to reflect the shift
                    shiftedNode[1] = *(int*)((int)prevNodeData + 4); // shifted node's next = previous node's next
                    *(int**)((int)prevNodeData + 4) = shiftedNode;   // previous node's next = shifted node
                }
            }
        }

        // Increment count after shifting
        thisPtr[1] = thisPtr[1] + 1;

        // Clear the slot at the insertion index
        int slotOffset = index * 8;
        if (*(int*)(*thisPtr + slotOffset) != 0)
        {
            FUN_004daf90(*thisPtr + slotOffset);
        }
        newSlot = (int*)(*thisPtr + slotOffset);
        if (newSlot != (int*)0x0)
        {
            *newSlot = 0;
            newSlot[1] = 0;
        }
        return (int)(*thisPtr + slotOffset);
    }
    else
    {
        // Inserting at the end: just clear the new slot and increment count
        if (nodePtr != (int*)0x0)
        {
            *nodePtr = 0;
            nodePtr[1] = 0;
        }
        thisPtr[1] = thisPtr[1] + 1;
        return (int)(*thisPtr + thisPtr[1] * 8 - 8); // Return pointer to the new slot (which is at old count)
    }
}