// FUNC_NAME: DoublyLinkedList::reinsertNode
void __thiscall DoublyLinkedList::reinsertNode(ListNode* node, ListManager* listMgr)
{
    // param_1 = node (ListNode*)
    // param_2 = listMgr (ListManager*)
    // node has fields:
    // +0x00: next (ListNode*)
    // +0x04: prev (ListNode*)
    // +0x08: currentListNode (ListNode*) – pointer to the node currently being managed (e.g. in a free list)
    // +0x15: flag byte in the node pointed by currentListNode

    // listMgr has fields:
    // +0x1c: someListHead (ListNode**) – pointer to a list head (possibly the master free list)

    ListNode* tempNode = node->currentListNode;         // piVar1 = *(node+8)
    node->currentListNode = tempNode->next;             // skip tempNode from its current list

    // If tempNode's flag byte (offset 0x15) is zero, set its prev to node
    if (*(char*)((int)tempNode + 0x15) == '\0') {
        tempNode->prev = node;
    }

    // Link tempNode after node's current previous neighbour
    tempNode->next = node->prev;                        // piVar1[1] = node->prev

    // Check if node is currently the last node of some container list
    ListNode* someHead = *(ListNode**)((int)listMgr + 0x1c); // listMgr->someListHead
    if (node == someHead->prev) {
        // Update the list head's prev to point to tempNode
        someHead->prev = tempNode;
        tempNode->next = node;                          // only needed if we are inserting before node?
        node->prev = tempNode;
        return;
    }

    // Otherwise, check if node is the first node after its predecessor
    ListNode* predNode = node->prev;                    // piVar2 = node->prev
    if (node == predNode->next) {
        // Update predecessor's next to point to tempNode
        predNode->next = tempNode;
        tempNode->next = node;
        node->prev = tempNode;
        return;
    }

    // General case: insert tempNode after predecessor's second successor? (original logic)
    predNode->next->next = tempNode;                    // predNode[2] = tempNode (assuming +0x08 is next->next?)
    tempNode->next = node;
    node->prev = tempNode;
}