// FUNC_NAME: DoublyLinkedList::unlinkNode
// Address: 0x004d1ea0
// Removes a node from a doubly linked list, updating the head/tail pointers.
// The node is an intrusive linked list node (next at +0x0, prev at +0x4).
// The list head/tail is passed as a pointer to a struct with head (+0x0) and tail (+0x4).

struct ListNode {
    ListNode* next; // +0x0
    ListNode* prev; // +0x4
};

struct ListHead {
    ListNode* head; // +0x0
    ListNode* tail; // +0x4
};

void __fastcall DoublyLinkedList::unlinkNode(ListNode* node, ListHead* list) {
    // If node is not the head, update previous node's next pointer
    if (node->prev == nullptr) {
        // Node is the head; new head becomes node->next
        list->head = node->next;
        if (node->next != nullptr) {
            // If there is a next node, clear its prev pointer
            node->next->prev = nullptr;
        }
        // If node was the only element, handle tail below (goto)
        if (node->next == nullptr) {
            // Node was both head and tail; list becomes empty
            list->tail = nullptr; // tail set to null via the branch below
            goto cleanupNode;
        }
    } else {
        // Node is not head; connect previous node directly to node->next
        node->prev->next = node->next;
    }

    // If node is not the tail, update next node's prev pointer
    if (node->next != nullptr) {
        node->next->prev = node->prev;
        node->prev = nullptr;
        node->next = nullptr;
        return;
    }

    // Node is the tail (or the only element already handled above)
    // Update tail pointer to the previous node
cleanupNode:
    ListNode* prevNode = node->prev;
    list->tail = prevNode;
    if (prevNode != nullptr) {
        prevNode->next = nullptr;
    }

    // Detach node from list entirely
    node->prev = nullptr;
    node->next = nullptr;
}