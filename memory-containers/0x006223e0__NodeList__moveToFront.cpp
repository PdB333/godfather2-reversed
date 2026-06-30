// FUNC_NAME: NodeList::moveToFront
// Function at 0x006223e0: Moves a node to the front of a linked list, removing it from its current position.
// The node structure: +0x00 next, +0x04 prev, +0x08 listOwner (pointer to the list it belongs to)
// The list structure: +0x04 head, +0x25 some flag (maybe bool m_bDisableAutoRemove)

void __thiscall NodeList::moveToFront(int *node, int *manager) {
    int *nextNode;      // original next of the node
    int *listPtr;       // pointer to the list container inside the node's next node
    int *managerList;   // list pointer from manager

    nextNode = (int *)*node;                         // node->next
    *node = *(int *)((int)nextNode + 8);             // node->next = nextNode->listOwner (skip?)

    // If the list owner of nextNode has its flag at +0x25 clear, update its head to this node
    if (*(char *)(*(int *)((int)nextNode + 8) + 0x25) == '\0') {
        *(int **)(*(int *)((int)nextNode + 8) + 4) = node; // listOwner->head = node
    }

    *(int *)((int)nextNode + 4) = node[1];           // nextNode->prev = node->prev

    // Check if node is the head of the list pointed by manager->list
    managerList = (int *)*(int *)(manager + 0x1c);   // get list pointer from manager offset 0x1c
    if (node == (int *)*(int *)((int)managerList + 4)) {  // if node == list->head
        *(int *)((int)managerList + 4) = (int)nextNode;   // list->head = nextNode
        *(int **)((int)nextNode + 8) = node;             // nextNode->listOwner = node (?) - actually sets the list owner of nextNode to node itself?
        node[1] = (int)nextNode;                         // node->prev = nextNode
        return;
    }

    // Otherwise, get the previous node of node
    int *prevNode = (int *)node[1];                  // node->prev
    if (node == (int *)prevNode[2]) {                // if node == prevNode->owner (?) - check if prevNode's owner list is the same? (likely last node condition)
        prevNode[2] = (int)nextNode;                 // prevNode->owner = nextNode
        *(int **)((int)nextNode + 8) = node;         // nextNode->listOwner = node
        node[1] = (int)nextNode;                     // node->prev = nextNode
        return;
    }

    // General case: link prevNode to nextNode
    *prevNode = (int)nextNode;                       // prevNode->next = nextNode
    *(int **)((int)nextNode + 8) = node;             // nextNode->listOwner = node
    node[1] = (int)nextNode;                         // node->prev = nextNode
    return;
}