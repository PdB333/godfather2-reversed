// FUNC_NAME: SomeClass::removeAllLinks
void __thiscall SomeClass::removeAllLinks(int linkArray)
{
    int head;
    int* nextNode;
    int* prevNode;
    int* currentNode;
    uint32 index;
    uint32* countPtr; // unaff_EDI - points to count of links in array

    if (linkArray != 0) {
        index = 0;
        currentNode = linkArray;
        // Count is stored in a global or member (unaff_EDI)
        if (*countPtr != 0) {
            do {
                head = *currentNode; // first word: pointer to list head
                if (head != 0) {
                    // head is a struct with at least a 'next' pointer at +0x04
                    nextNode = *(int**)(head + 4);
                    if (nextNode == currentNode) {
                        // The first node in the list is the one we're removing
                        *(int*)(head + 4) = currentNode[1]; // head->next = currentNode->next
                    } else {
                        // Walk the list to find the node before currentNode
                        prevNode = nextNode;
                        currentNode = (int*)prevNode[1];
                        while (currentNode != (int*)linkArray + index*3) { // currentNode == current entry address?
                            prevNode = currentNode;
                            currentNode = (int*)prevNode[1];
                        }
                        prevNode[1] = ((int*)linkArray + index*3)[1]; // prev->next = currentNode->next
                    }
                }
                index++;
                currentNode += 3; // each entry is 12 bytes (3 ints)
            } while (index < *countPtr);
        }
        // Call deallocation function via vtable at +0x10 (offset 4)
        (**(code **)(**(int **)(this + 0x10) + 4))(linkArray, 0);
    }
    return;
}