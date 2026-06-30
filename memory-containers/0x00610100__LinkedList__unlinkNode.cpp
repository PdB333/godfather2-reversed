// FUNC_NAME: LinkedList::unlinkNode
void __thiscall LinkedList::unlinkNode(LinkedList *this, ListNode *node) {
    ListNode *nextNode; // param_2+0x88
    ListNode *prevNode; // param_2+0x8c

    nextNode = *(ListNode **)(node + 0x88);   // node->next
    prevNode = *(ListNode **)(node + 0x8c);   // node->prev

    if (nextNode != NULL) {
        *(ListNode **)(nextNode + 0x8c) = prevNode;  // nextNode->prev = prevNode
    }
    if (prevNode != NULL) {
        *(ListNode **)(prevNode + 0x88) = nextNode;  // prevNode->next = nextNode
    }
    // if node is the head, update head to next
    if (*(ListNode **)(this + 0x84) == node) {
        *(ListNode **)(this + 0x84) = nextNode;   // this->head = nextNode
    }
    // clear node's links and data pointer (or some other field)
    *(uint32_t *)(node + 0x8c) = 0;   // node->prev = NULL
    *(uint32_t *)(node + 0x88) = 0;   // node->next = NULL
    *(uint32_t *)(node + 0x80) = 0;   // node->data = NULL (or other)
}