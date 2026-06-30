// FUNC_NAME: LinkedList::removeAllByKey
// Address: 0x006f2ea0
// Removes all nodes from the list whose data matches the given key.
// Uses internal helper removeNode to perform unlinking and memory management.

void __thiscall LinkedList::removeAllByKey(int *keyPtr)
{
    ListNode *currentNode;      // ecx, local_4
    ListNode **currentPtr;      // used during removal
    ListNode *nextNode;         // result from removeNode

    currentNode = this->head;   // this->head at offset 0

    while (currentNode != nullptr) {
        if (*keyPtr == currentNode->data) {
            // Remove this node. removeNode takes address of head and the node to remove,
            // returns a pointer to the pointer to the next node (or the new head if head removed).
            nextNode = (ListNode *)LinkedList::removeNode(&this->head, currentNode);
            currentNode = nextNode;
        } else {
            currentNode = currentNode->next; // offset 4
        }
    }
}