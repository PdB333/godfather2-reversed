// FUNC_NAME: LinkedList::destroyAll
// Function at 0x00648b60 - Destructor/cleanup for a doubly-linked list with sub-lists and critical section
// This appears to be a container class that manages a list of nodes, each node may contain a sub-list.
// The class has a flag at +0x00, a sentinel head at +0x04, a pointer to first node at +0x1c,
// another sentinel at +0x2c, a callback function pointer at +0x190 (400 decimal), and a critical section pointer at +0x1b8.

int LinkedList::destroyAll()
{
    // Check if the container is initialized (flag at +0x00)
    if (this->flag != '\0') {
        this->flag = '\0';
        // Call a helper function to clear the list (likely removes all nodes)
        FUN_0064a740(); // Probably LinkedList::clearInternal or similar

        // Iterate through the main list starting from the first node (at +0x1c)
        Node* currentNode = this->firstNode; // +0x1c
        while (currentNode != &this->headSentinel) { // +0x04 is head sentinel
            // For each node, iterate through its sub-list (starting at node+0x10)
            Node* subNode = currentNode->subListHead; // +0x10
            while (subNode != currentNode) {
                // Call the callback function for each sub-node
                (this->callback)(); // +0x190
                subNode = subNode->subListHead; // Move to next sub-node
            }

            // Unlink the current node from the main list (doubly linked)
            // node+0x14 = prev, node+0x18 = next
            currentNode->prev->next = currentNode->next;
            currentNode->next->prev = currentNode->prev;

            // If the node has a custom destructor, call it
            if (currentNode->destructor != nullptr) { // +0x20
                currentNode->destructor();
            }

            // If the current node is not the second sentinel (at +0x2c), call the callback again
            if (currentNode != &this->secondSentinel) { // +0x2c
                (this->callback)();
            }

            // Move to the next node in the main list
            currentNode = this->firstNode; // +0x1c (updated after unlinking)
        }
    }

    // Delete the critical section if it exists
    if (this->criticalSection != nullptr) { // +0x1b8
        DeleteCriticalSection(this->criticalSection);
        // Zero out the critical section pointer (4 bytes)
        this->criticalSection = nullptr; // +0x1b8 to +0x1bb
    }

    return 1;
}