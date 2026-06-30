// FUNC_NAME: removeLinkNode (static utility: remove a node from a doubly linked list and update head/tail)
// Address: 0x004492b0
// Role: Removes a LinkNode from a doubly linked list managed by a LinkList structure.
// The list structure has head at offset 0 and tail at offset 4.
// Node structure: next at offset 0, prev at offset 4.

// Represents a node in a doubly linked list
struct LinkNode {
    LinkNode* next; // +0x00
    LinkNode* prev; // +0x04
};

// Represents a doubly linked list with head and tail pointers
struct LinkList {
    LinkNode* head; // +0x00
    LinkNode* tail; // +0x04
};

// Fastcall: node in ECX, list in EDX
void __fastcall removeLinkNode(LinkNode* node, LinkList* list)
{
    if (node->prev == nullptr) {
        // Node is the head of the list
        list->head = node->next;
        if (list->head != nullptr) {
            list->head->prev = nullptr;
        }
    } else {
        // Node is not the head; stitch previous node's next pointer
        node->prev->next = node->next;
    }

    if (node->next != nullptr) {
        // Node is not the tail; stitch next node's prev pointer
        node->next->prev = node->prev;
        // Clear the node's own pointers
        node->prev = nullptr;
        node->next = nullptr;
    } else {
        // Node is the tail; update tail to previous node
        list->tail = node->prev;
        if (list->tail != nullptr) {
            list->tail->next = nullptr;
        }
        // Clear the node's own pointers
        node->prev = nullptr;
        node->next = nullptr;
    }
}