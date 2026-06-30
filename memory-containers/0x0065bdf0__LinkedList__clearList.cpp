// FUNC_NAME: LinkedList::clearList
// Address: 0x0065bdf0
// Purpose: Iterates through a singly linked list, destroying each node's associated data and freeing the node.
// List node layout: offset 0 = next pointer, offset 4 = data pointer.
// The head pointer is stored at the beginning of the object (this).

void LinkedList::clearList(void)
{
    int* head = reinterpret_cast<int*>(this);   // +0x00: head pointer
    int* currentNode = *head;                   // iVar1
    while (currentNode != nullptr) {
        int* nextNode = reinterpret_cast<int*>(*currentNode); // next node at node+0
        if (currentNode != nullptr) {
            // Destroy the data object referenced by node[1]
            destroyData(reinterpret_cast<void*>(currentNode[1])); // FUN_009c8f10
            // Deallocate the node itself
            freeNode(currentNode);                               // FUN_009c8eb0
        }
        *head = nextNode;   // update head to next
        currentNode = nextNode;
    }
}