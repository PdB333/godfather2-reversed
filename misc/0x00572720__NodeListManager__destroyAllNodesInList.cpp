// FUNC_NAME: NodeListManager::destroyAllNodesInList
void NodeListManager::destroyAllNodesInList() {
    // Get head of node list stored at this + 0x124
    Node* head = *(Node**)((char*)this + 0x124);
    if (head == nullptr) {
        return;
    }

    int index = 0;
    while (true) {
        // Traverse to the index-th node (0-based) from head each time
        Node* currentNode = head;
        int steps = 0;
        if (index > 0) {
            do {
                // Next pointer stored at offset 0x124 within each node
                currentNode = *(Node**)((char*)currentNode + 0x124);
                if (currentNode == nullptr) {
                    return;
                }
                steps++;
            } while (steps < index);
        }

        // Stop if we reached end of list
        if (currentNode == nullptr) {
            break;
        }

        // Call vtable function at index 1 (offset +4) with argument -1 (destroy/release)
        auto vtable = *(int**)currentNode;
        auto destroyFunc = (void(__thiscall*)(Node*, int))(vtable[1]);

        // Reset state: clears int at offset 0x110 and byte flag at offset 0x121
        *(int*)((char*)currentNode + 0x110) = 0;
        *(char*)((char*)currentNode + 0x121) = 0;

        // Invoke destructor-style method
        destroyFunc(currentNode, -1);

        index++;
    }
}