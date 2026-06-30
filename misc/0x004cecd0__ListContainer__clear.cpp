// FUNC_NAME: ListContainer::clear
void ListContainer::clear() {
    // Get the sentinel node pointer (offset 0x18)
    Node* sentinel = reinterpret_cast<Node*>(this->m_sentinelPtr);  // this+0x18
    // Get the first actual node (next of sentinel)
    Node* currentNode = sentinel->next;
    
    // Reset sentinel to point to itself (empty list)
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    
    // Reset count (offset 0x1C)
    this->m_count = 0;  // this+0x1C
    
    // Iterate through the list and delete each node
    while (currentNode != sentinel) {
        Node* nextNode = currentNode->next;
        // Call virtual destructor/release function (vtable+4) with size parameter 0xc
        (this->vtable->destroyNode)(currentNode, 0xc);  // size hint for deallocation
        currentNode = nextNode;
    }
}