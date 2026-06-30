// FUNC_NAME: ObjectListManager::processListNodes
bool ObjectListManager::processListNodes() {
    // Offset +0x08: pointer to a container structure
    Container* container = *(Container**)(this + 0x08);
    bool foundDead = false;

    if (container == nullptr) {
        foundDead = true;
    } else {
        // Offset +0x1c in container: pointer to pointer to first node (double indirection)
        Node* currentNode = **(Node***)(container + 0x1c);
        while (true) {
            // Re-fetch head pointer from container (+0x1c)
            Node* headNode = *(Node**)(container + 0x1c);

            // Assertion checks (likely debug-only)
            if ((currentNode == nullptr) || (currentNode != (Node*)(container + 0x1c))) {
                assertionError(); // FUN_00b97aea
            }
            if (currentNode == headNode) break;
            if (currentNode == nullptr) {
                assertionError();
            }
            if (currentNode == *(Node**)(container + 0x1c)) {
                assertionError();
            }

            // Offset +0x10 in node: flag (0 = inactive/dead)
            if (*(int*)(currentNode + 0x10) == 0) {
                foundDead = true;
                processDeadNode();   // FUN_005e09e0
            } else {
                updateNode();        // FUN_005dd660
                processDeadNode();   // FUN_005e09e0
            }
        }
    }
    return !foundDead;
}