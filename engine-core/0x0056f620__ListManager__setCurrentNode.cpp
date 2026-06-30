// FUNC_NAME: ListManager::setCurrentNode
void ListManager::setCurrentNode(Node* node) {
    // Increment reference count of the new node (byte at +0x9)
    if (node != nullptr) {
        ++node->refCount;
    }

    Node* oldNode = this->currentNode; // +0x34
    if (oldNode != nullptr) {
        --oldNode->refCount;

        // If the old node is not flagged and has no references, remove it from the list
        if (oldNode->flags == 0 && oldNode->refCount == 0) {
            Node* prevNode = oldNode->prev; // +0x0
            Node* nextNode = oldNode->next; // +0x4

            if (prevNode != nullptr) {
                prevNode->next = nextNode;
            }

            // Global list manager (DAT_01205564) – assumed structure:
            // +0x0: head, +0x4: last, +0x8: tail, +0xC: placeholder
            GlobalListManager* globList = g_listManager; 
            if (nextNode != nullptr) {
                nextNode->prev = prevNode;
                this->currentNode = node;
                return;
            }

            // No next node -> we are removing the tail
            globList->tail = globList->last;   // +0x8 = +0x4
            globList->last = prevNode;          // +0x4 = prevNode
            if (prevNode == nullptr) {
                globList->tail = globList->placeholder; // +0x8 = +0xC
            }
        }
    }

    this->currentNode = node;
}