// FUNC_NAME: ListHead::unlinkNode

#include <cstdint>

// Node element in a doubly linked list
// Offsets: +0x0: data (ignored), +0x4: data (ignored), +0x8: prev, +0xC: next
class Node {
public:
    // +0x8: pointer to previous node
    Node* prev;
    // +0xC: pointer to next node
    Node* next;
};

// Doubly linked list head/tail structure
// Offsets: +0x0: head, +0x4: tail
class ListHead {
public:
    Node* head; // +0x0
    Node* tail; // +0x4

    // Remove `node` from this list, updating head/tail as needed.
    // The node is assumed to belong to this list.
    void __thiscall unlinkNode(Node* node);
};

void __thiscall ListHead::unlinkNode(Node* node)
{
    // Handle removal when node is the tail (next == 0)
    if (node->next == nullptr) {
        // Update head: the new head becomes node's previous element
        head = node->prev;
        if (head != nullptr) {
            head->next = nullptr;
        }
    } else {
        // Bypass node: next node's previous becomes node's previous
        node->next->prev = node->prev;
    }

    // Handle removal when node is not the head (prev != 0)
    if (node->prev != nullptr) {
        // Bypass node: previous node's next becomes node's next
        node->prev->next = node->next;
        // Clear node's links
        node->next = nullptr;
        node->prev = nullptr;
        return;
    }

    // Node is the head (prev == 0):
    // Update tail to the element that was after node (could be null)
    tail = node->next;
    if (tail != nullptr) {
        tail->prev = nullptr;
    }
    // Clear node's links
    node->next = nullptr;
    node->prev = nullptr;
}