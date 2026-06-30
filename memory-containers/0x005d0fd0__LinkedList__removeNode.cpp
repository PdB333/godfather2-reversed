// FUNC_NAME: LinkedList::removeNode
// Function address: 0x005d0fd0
// Removes a node from a singly linked list with head and tail pointers,
// then deletes the node (calls destroy function at 0x005d12b0).
// Assumes the node to remove is either the head or the tail.
// Does not update previous node's next pointer if removing from middle.

typedef struct Node {
    int unknownFields[8];  // +0x00 to +0x1F
    Node* next;            // +0x20
} Node;

class LinkedList {
private:
    Node* head;   // +0x00
    Node* tail;   // +0x04

    // Reconstructed external deallocation function
    void destroyNode(Node* node);  // corresponds to FUN_005d12b0

public:
    __thiscall void removeNode(Node* node) {
        if (node == 0) {
            return;
        }

        // If node is the tail, update tail to its next (which becomes new tail)
        if (tail == node) {
            tail = node->next;
        }

        // If node is the head, update head to its next
        if (head == node) {
            head = node->next;
        }

        // Deallocate the node
        destroyNode(node);
    }
};