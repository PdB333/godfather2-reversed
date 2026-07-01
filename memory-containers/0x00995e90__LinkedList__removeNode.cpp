// FUNC_NAME: LinkedList::removeNode
void __thiscall LinkedList::removeNode(int *thisList, int unusedParam, int **iteratorPtr)
{
    int *nodeToRemove;
    int *nextNode;
    int *prevNode;

    nodeToRemove = *iteratorPtr;
    if (nodeToRemove == (int *)0x0) {
        nextNode = (int *)0x0;
    }
    else {
        nextNode = (int *)*((int *)nodeToRemove + 1); // node->next at offset +4
    }
    *iteratorPtr = nextNode; // advance iterator to next node

    if (nodeToRemove == (int *)*thisList) { // node is head
        if (nodeToRemove == (int *)thisList[1]) { // node is also tail (only one node)
            thisList[1] = 0; // tail = null
            *thisList = 0;   // head = null
        }
        else {
            nextNode = (int *)*((int *)nodeToRemove + 1); // node->next
            *thisList = (int)nextNode; // head = next
            if (nextNode != (int *)0x0) {
                *((int *)nextNode + 2) = 0; // new head->prev = null (offset +8)
            }
        }
    }
    else {
        prevNode = (int *)*((int *)nodeToRemove + 2); // node->prev at offset +8
        if (nodeToRemove == (int *)thisList[1]) { // node is tail
            thisList[1] = (int)prevNode; // tail = prev
            *((int *)prevNode + 1) = 0; // new tail->next = null (offset +4)
        }
        else {
            *((int *)prevNode + 1) = *((int *)nodeToRemove + 1); // prev->next = node->next
            *((int *)*((int *)nodeToRemove + 1) + 2) = *((int *)nodeToRemove + 2); // node->next->prev = node->prev
        }
    }
    // Call allocator's deallocate function (vtable entry at offset 4)
    (**(code **)(*(int *)thisList[4] + 4))(nodeToRemove, 0);
    thisList[2] = thisList[2] - 1; // decrement count
    // *unaff_EBX = *iteratorPtr; // side effect on register, omitted
}