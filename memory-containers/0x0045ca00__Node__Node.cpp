// FUNC_NAME: Node::Node
// Function address: 0x0045ca00
// Constructor for an intrusive doubly-linked list node.
// Inserts the new node into the circular list immediately after the head sentinel.
// The list uses a trick where each node's 'prev' field stores the address of the
// previous node's 'next' pointer, allowing O(1) removal without testing for head.
// The head sentinel is assumed to be located at 'headNode' (e.g., embedded in an
// owner object at a fixed offset +0x48).

// Node layout:
// +0x00: vtable (pointer to virtual function table)
// +0x04: next (Node*)
// +0x08: prev (Node**) - points to the 'next' field of the previous node

struct Node {
    void** vtable;   // +0x00
    Node* next;      // +0x04
    Node** prev;     // +0x08 (pointer to previous node's next)
};

// External vtable for this node type
extern void* sNodeVTable;  // originally PTR_FUN_00e31e2c

void __thiscall Node::Node(Node* this, Node* headNode)
{
    // Set virtual function table
    this->vtable = &sNodeVTable;

    // Link this node after the head sentinel
    this->next = headNode;              // new node points to head
    this->prev = headNode->prev;        // inherit head's previous link

    // Update head's previous link to point to this node's 'next' field
    headNode->prev = &(this->next);
}