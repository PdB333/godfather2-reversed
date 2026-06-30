// FUNC_NAME: DoublyLinkedList::unlinkNode
// Function address: 0x006f2c50
// This function removes a node from a doubly-linked list and calls its destructor.
// The node pointer is passed as a reference (int** ppNode) and updated to point to the next node (or NULL).
// The list structure (this) has:
//   +0x00: head pointer
//   +0x04: tail pointer
//   +0x08: count
//   +0x10: pointer to an allocator object with a virtual destructor/free function at vtable[1]
// Node structure (Node):
//   +0x00: data (unused here)
//   +0x04: next pointer
//   +0x08: prev pointer

class DoublyLinkedList {
public:
    struct Node {
        Node* prev; // +0x08
        Node* next; // +0x04
        // +0x00: other data
    };

    struct Allocator {
        virtual void releaseNode(Node* node, int flag); // vtable[1], `flag` typically 0
    };

    Node* head;          // +0x00
    Node* tail;          // +0x04
    int count;           // +0x08
    Allocator* allocator; // +0x10

    // Remove the node pointed to by *ppNode from the list,
    // update *ppNode to the node that followed it (or NULL),
    // call allocator->releaseNode(node, 0),
    // and decrement the count.
    // The parameter `unused` (second stack param) is ignored.
    void __thiscall unlinkNode(Node*& rpNode) {
        Node* node = rpNode;
        Node* next = (node != nullptr) ? node->next : nullptr;

        // Update the output pointer to the next node
        rpNode = next;

        if (node == head) {
            if (node == tail) {
                // List becomes empty
                tail = nullptr;
                head = nullptr;
            } else {
                // Removing head, update head to next node
                head = next;
                if (next != nullptr) {
                    next->prev = nullptr;
                }
            }
        } else {
            Node* prev = node->prev; // node is not head, prev is non-null
            if (node == tail) {
                // Removing tail, update tail to previous node
                tail = prev;
                prev->next = nullptr;
            } else {
                // Removing middle node
                prev->next = next;
                if (next != nullptr) {
                    next->prev = prev;
                }
            }
        }

        // Call allocator's destructor/release on the removed node
        allocator->releaseNode(node, 0);

        // Decrement count
        count--;
    }
};