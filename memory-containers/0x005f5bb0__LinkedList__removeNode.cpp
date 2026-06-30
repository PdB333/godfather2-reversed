// FUNC_NAME: LinkedList::removeNode
void __fastcall LinkedList::removeNode(int* nodeToRemove)
{
    int* listHead = (int*)*nodeToRemove;
    if (listHead == nullptr) {
        return;
    }

    int** headNextField = (int**)(listHead + 1); // offset +4: pointer to first node
    int* firstNode = *headNextField;
    if (firstNode == nodeToRemove) {
        // Removing the first node in the list
        *headNextField = (int*)nodeToRemove[1]; // nodeToRemove->next becomes new head
        return;
    }

    // Traverse the list to find the node before nodeToRemove
    int* prevNode = firstNode;
    int* currentNode = (int*)prevNode[1]; // next node
    while (currentNode != nodeToRemove) {
        prevNode = currentNode;
        currentNode = (int*)prevNode[1];
    }

    // Bypass the removed node
    prevNode[1] = nodeToRemove[1];
}