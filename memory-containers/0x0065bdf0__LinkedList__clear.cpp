// FUNC_NAME: LinkedList::clear
void LinkedList::clear() {
    // Iterate through linked list and delete all nodes
    // Node structure: +0x00 next, +0x04 data pointer
    // head pointer stored at this+0x00
    int* headNode = reinterpret_cast<int*>(this->head);
    while (headNode != nullptr) {
        int* nextNode = reinterpret_cast<int*>(*headNode);
        if (headNode != nullptr) {
            // Free the data associated with the node (calls operator delete or custom free)
            FUN_009c8f10(headNode[1]);
            // Free the node itself (calls operator delete or custom free)
            FUN_009c8eb0(headNode);
        }
        // Advance head pointer to next node
        this->head = nextNode;
        headNode = reinterpret_cast<int*>(this->head);
    }
}