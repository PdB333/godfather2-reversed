// FUNC_NAME: NodeList::relinkNode
void __thiscall NodeList::relinkNode(Node* node, ListRoot* newList)
{
    // node: pointer to the node to be relocated (param_1)
    // newList: pointer to the destination list root structure (param_2)
    Node* nextNode = node->next; // +0x8: next pointer

    // Unlink node from its current list by updating node->next to point to the next node's next?
    // Actually this is a custom list manipulation: it seems to remove the next node from its position
    // and prepare node to be inserted elsewhere.
    node->next = (Node*)nextNode->prev; // *nextNode interpreted as int (first field = prev?) sets node->next to nextNode->prev

    // If the next node has some flag at offset 0x15 of its data? (maybe a sentinel flag)
    // *piVar1+0x15 is a byte, likely a marker for head/tail.
    if (*(char*)((int)nextNode + 0x15) == 0) {
        nextNode->prev = node; // Set the next node's prev to this node
    }

    nextNode->prev = node->prev; // Set nextNode->prev to node's prev

    // Now check if node is the tail of the new list (newList->tail == node?)
    Node** tailPtr = (Node**)(*(int*)(newList + 0x1c) + 4); // +0x1c points to a structure, +4 is tail pointer
    if (node == *tailPtr) {
        // If node was the tail, then update the tail to nextNode and set node's next to nextNode
        *tailPtr = nextNode;
        nextNode->next = node;
        node->prev = nextNode;
        return;
    }

    Node* prevNode = node->prev;
    if (node == prevNode->next) {
        // If node is the next of its previous node (i.e., node is the head of its sublist?)
        // Update prevNode->next to nextNode
        prevNode->next = nextNode;
        nextNode->next = node;
        node->prev = nextNode;
        return;
    }

    // General case: update prevNode's next to nextNode
    prevNode->next = nextNode;
    nextNode->next = node;
    node->prev = nextNode;
}