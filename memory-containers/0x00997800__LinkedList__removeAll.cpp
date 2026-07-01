// FUNC_NAME: LinkedList::removeAll

// Function at 0x00997800
// Removes all nodes from a singly linked list that match a given integer value.
// This is a member function of a list class where `this` points to a struct with a `head` pointer at offset 0.
// Each node is 8 bytes: integer value at +0, next pointer at +4.
// The helper function `removeNode` (0x00995e90) performs the actual removal and returns a pointer to
// the next node's location (or updated head pointer). The parameters to `removeNode` are passed as
// `&value` and `&currentNode` – note: due to decompilation artifacts, the actual intended parameters
// may be the head pointer and node pointer; but the logic is preserved as decompiled.

void __thiscall LinkedList::removeAll(int* valuePtr)
{
    // `piVar1` holds the pointer to the value to compare
    int* searchVal = valuePtr;          // param_2
    // `local_4` = current node pointer, initially head of list
    int* currentNode = reinterpret_cast<int*>(*reinterpret_cast<int*>(this)); // *param_1 = this->head

    while (currentNode != nullptr)
    {
        // Compare the value at current node with the search value
        if (*searchVal == *currentNode)   // if (*piVar1 == *local_4)
        {
            // Remove the current node from the list
            // `removeNode` returns a pointer to a pointer which holds the next node (or updated head)
            int** nextPtr = reinterpret_cast<int**>(FUN_00995e90(&valuePtr, &currentNode));
            currentNode = reinterpret_cast<int*>(*nextPtr); // move to next node after removal
        }
        else
        {
            // No match: advance to next node
            currentNode = reinterpret_cast<int*>(currentNode[1]); // local_4[1] = next pointer
        }
    }
}