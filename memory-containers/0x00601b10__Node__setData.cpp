// FUNC_NAME: Node::setData
// Function address: 0x00601b10
// Role: Sets the data pointer of a linked list node, managing insertion/removal from a list keyed by the data pointer.
// The node must have fields:
//   data (void*, offset 0x00)
//   next (Node*, offset 0x04)
// The data objects are assumed to have a next pointer at offset 0x04 that acts as a list head.
// When the data changes, the node removes itself from the old data's list and inserts itself into the new data's list.

struct Node {
    void* data;   // +0x00
    Node* next;   // +0x04
};

// Forward declaration of the removal helper (defined elsewhere, at 0x004daf90)
void removeNodeFromList(Node* node); // Removes the node from whatever list it is currently linked in

Node* __thiscall Node::setData(void* newData) {
    if (this->data != newData) {
        if (this->data != nullptr) {
            removeNodeFromList(this); // Unlink from old data's list
        }
        this->data = newData;
        if (newData != nullptr) {
            Node* container = static_cast<Node*>(newData); // Treat newData as a Node (list head)
            this->next = container->next;                 // Point this node to the container's next
            container->next = this;                       // Insert this node immediately after container
        }
    }
    return this;
}