// FUNC_NAME: NodeList::insertAfter

/**
 * @brief Inserts a new node after the node pointed to by the current iterator position.
 * 
 * The function allocates a new node of size 0xC (12 bytes) from a custom memory pool
 * and inserts it into a global doubly linked list after the node stored in the
 * "currentNode" member (accessed via *this). The list's head is maintained globally
 * at DAT_012224ac, and count at DAT_012224b4.
 * 
 * Node structure (12 bytes):
 *   +0x00: data pointer (stored from the return address value)
 *   +0x04: pointer to previous node
 *   +0x08: pointer to next node
 *
 * @param outNewNode Output pointer that receives the address of the newly inserted node.
 *                   The function returns this pointer for chaining.
 * @return The same pointer passed as outNewNode, now pointing to the new node.
 */
void** __thiscall NodeList::insertAfter(void** outNewNode)
{
    // Get the node after which to insert from the current iterator position.
    // 'this' points to an object whose first member is a pointer to a node (currentNode).
    Node* currentNode = *(Node**)(this);
    
    // Determine the memory region to use for allocation.
    // Default region is a static buffer (DAT_01218a14) if the global region is null.
    void* region = (void*)DAT_012224b8;
    if (region == nullptr) {
        region = &DAT_01218a14;        // Static fallback arena
    }
    
    // Allocate a new node (0xC bytes) using a custom allocator function.
    // The allocator function pointer is stored at DAT_012224bc.
    Node* newNode = (Node*)((*(allocFunc) * DAT_012224bc)(0xC, region));
    
    if (newNode != nullptr) {
        // Initialize the new node: store the data from the return address (unaff_retaddr)
        newNode->data = (void*)(unaff_retaddr);   // unaff_retaddr is the saved return address? 
        newNode->prev = nullptr;
        newNode->next = nullptr;
    }
    
    // Link the new node into the list.
    if (currentNode == (Node*)DAT_012224ac) {   // Inserting after the head?
        // Special case: the current node is the head, so the new node becomes the new head.
        newNode->next = nullptr;                 // Since it's after head, no previous? Actually we set next to 0 then adjust.
        DAT_012224ac = newNode;
    } else {
        // Insert after the current node.
        Node* nextNode = currentNode->next;      // Node that was after currentNode
        newNode->next = nextNode;
        if (nextNode != nullptr) {
            nextNode->prev = newNode;
        }
    }
    
    // Set the new node's previous pointer to the current node.
    newNode->prev = currentNode;
    // Update the current node's next pointer to the new node.
    currentNode->next = newNode;
    
    // Increment the global node count.
    DAT_012224b4++;
    
    // Store the new node's address into the output parameter.
    *outNewNode = newNode;
    
    return outNewNode;   // Allows chaining
}