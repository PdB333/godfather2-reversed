// FUNC_NAME: EARSLinkedList::clearList

void __fastcall EARSLinkedList::clearList(int thisPtr)
{
    int *storedObject;
    int *oldNextNode;
    int *currentNode;
    int allocatorData;

    // Iterate over all nodes in the doubly-linked circular list (dummy head at thisPtr+0x24)
    for (currentNode = (int *)**(int **)(thisPtr + 0x24);
         currentNode != *(int **)(thisPtr + 0x24);
         currentNode = (int *)*currentNode)
    {
        // Unreachable assertion: should never process the dummy head
        if (currentNode == *(int **)(thisPtr + 0x24)) {
            FUN_00b97aea(); // assert failure
        }

        // storedObject is the data pointer stored in the node at offset +8
        storedObject = (int *)currentNode[2]; // node[2] = offset 8
        // Release or decrement reference for internal structures (at storedObject+8)
        FUN_004086d0(storedObject + 8); // offset 0x20? likely a sub-object
        FUN_00408310(storedObject + 8); // another release

        // If storedObject has a second data pointer at offset 0x10 (storedObject[4]),
        // call its destructor (through vtable at storedObject[7], offset 0x1c)
        if (storedObject[4] != 0) {
            (*(code *)storedObject[7])(storedObject[4]); // storedObject[4] as this
        }

        // If storedObject itself has a pointer at offset 0 (storedObject[0]),
        // call its destructor (through vtable at storedObject[3], offset 0xc)
        if (*storedObject != 0) {
            (*(code *)storedObject[3])(*storedObject); // storedObject[0] as this
        }

        // Deallocate the stored object using a global deallocator
        allocatorData = *(int *)(thisPtr + 0x2c); // +0x2c: some allocator state
        (*DAT_012059e0)(storedObject); // call global free or dealloc function
        if (allocatorData != 0) {
            storedObject = (int *)(*(int *)(allocatorData + 0x10) + 0x24);
            *storedObject = *storedObject - 0x28; // adjust some counter
        }

        // Unreachable assertion again
        if (currentNode == *(int **)(thisPtr + 0x24)) {
            FUN_00b97aea();
        }
    }

    // Reset the linked list to empty (dummy node points to itself)
    storedObject = *(int **)(thisPtr + 0x24); // head pointer (dummy)
    oldNextNode = (int *)*storedObject;       // save original first node
    *storedObject = (int)storedObject;        // head->next = head
    *(int *)(*(int *)(thisPtr + 0x24) + 4) = *(int *)(thisPtr + 0x24); // head->prev = head
    *(int *)(thisPtr + 0x28) = 0;             // +0x28: count = 0

    // Free all nodes that were in the list (size 0xc each)
    if (oldNextNode != *(int **)(thisPtr + 0x24)) {
        do {
            storedObject = (int *)*oldNextNode; // save next node
            // Call vtable function at (thisPtr->m_allocator)+4 to free the node
            (**(code **)(**(int **)(thisPtr + 0xc) + 4))(oldNextNode, 0xc);
            oldNextNode = storedObject;
        } while (storedObject != (int *)*(int *)(thisPtr + 0x24));
    }
}