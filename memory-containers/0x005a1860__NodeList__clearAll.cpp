// FUNC_NAME: NodeList::clearAll
// Function address: 0x005a1860
// Iterates a singly-linked list stored in the owning object (head at this+0x00),
// calling a global cleanup function pointer on each node (node->next at +0x04),
// then updates the head pointer. Finally calls a global finaliser.
void NodeList::clearAll() {
    Node* pCurrent = this->head;  // head at offset 0x00
    while (pCurrent != nullptr) {
        pCurrent = this->head;    // re-fetch head (safety)
        if (pCurrent != nullptr) {
            Node* pNext = pCurrent->next;   // next at offset +0x04
            // Release the node using the global deleter (set by constructor)
            g_pNodeDeleteFunc(pCurrent);    // DAT_0119caf4
            this->head = pNext;             // advance head
        }
        pCurrent = this->head;    // re-check head
    }
    // Final cleanup on the container itself
    g_pListCleanupFunc();          // DAT_0119caf8
}