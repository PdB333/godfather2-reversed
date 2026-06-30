// FUNC_NAME: EntityManager::releaseObjectByID
void EntityManager::releaseObjectByID(int objectID) {
    // +0x10: pointer to ObjectList (custom linked list)
    ObjectList* list = *(ObjectList**)(this + 0x10);
    // List nodes: sentinel at list->sentinel (+0x1c), node->next at +0x00, node->data at +0x10
    ObjectListNode* currentNode = list->sentinel->next; // first real node
    ObjectListNode* sentinelNode = list->sentinel;

    while (true) {
        // Validate list integrity
        if (currentNode == nullptr || currentNode != *(ObjectListNode**)(this + 0x10)) {
            FUN_00b97aea(); // assertion failure
        }
        if (currentNode == sentinelNode) break;

        if (currentNode == nullptr) {
            FUN_00b97aea();
        }
        if (currentNode == sentinelNode->next) { // duplicate check? actual condition: currentNode == sentinelNode->next
            FUN_00b97aea();
        }

        // Get the actual data object from the node
        // +0x10: pointer to the managed object (e.g., an Effect or Entity)
        EARSObject* obj = *(EARSObject**)(currentNode + 0x10);
        int id = *(int*)(obj + 0x290); // object's unique ID

        if (id == objectID) {
            // Clear the object if it is currently active
            if (*(char*)(obj + 4) != '\0' && id != 0) {
                FUN_005ddd90(gGlobalManager, id); // likely a destruction/release function
                *(char*)(obj + 4) = 0; // clear active flag
            }
            *(int*)(obj + 0x290) = 0; // clear ID field
        }

        // Move to next node (FUN_004cab50 advances the iterator)
        currentNode = FUN_004cab50(currentNode); // assumed to return next node or handle iteration
    }
}