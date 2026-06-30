// FUNC_NAME: ObjectList::moveToFront
// Function address: 0x00446680
// Moves a node to the front of a doubly linked list. The list head is stored at this+0x6c.
// Node structure: prev at +0x0c, next at +0x10.

void __thiscall ObjectList::moveToFront(ObjectNode* node) {
    // Only move if node is currently in a list (prev non-null)
    if (node->prev != nullptr) {
        // Remove node from its current list
        // Update previous node's next pointer to skip this node
        *node->prev = node->next; // ** Note: prev points to the pointer that points to this node (either head or previous node's next)
        
        // If there is a next node, update its prev to point to this node's old prev
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
        
        // Reset node's prev and next to null
        node->next = nullptr;
        node->prev = nullptr;
        
        // Insert node at head of this list
        NodeHeader* headPtr = reinterpret_cast<NodeHeader*>(reinterpret_cast<char*>(this) + 0x6C);
        node->next = *headPtr;            // node->next = old head
        node->prev = headPtr;             // prev points to the head pointer itself
        if (*headPtr != nullptr) {
            (*headPtr)->prev = &node->next; // old head's prev points to new node's next field
        }
        *headPtr = node;                  // head now points to this node
    }
}