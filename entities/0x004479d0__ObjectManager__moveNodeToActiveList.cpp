// FUNC_NAME: ObjectManager::moveNodeToActiveList
void ObjectManager::moveNodeToActiveList(int id) {
    // Check if already in the "processed" or "deleted" lists
    for (Node* node = listA; node != nullptr; node = node->next) {
        if (node->id == id) {
            return; // Already in listA
        }
    }
    for (Node* node = headActive; node != nullptr; node = node->next) {
        if (node->id == id) {
            return; // Already in active list
        }
    }

    // Search in the "pending" list (listB)
    Node* node = listB;
    while (node != nullptr) {
        if (node->id == id) {
            if (node != nullptr) {
                lockList(); // Remove from pending list
                node->next = nullptr;
                node->prev = tailActive;
                if (tailActive != nullptr) {
                    tailActive->next = node;
                    tailActive = node;
                } else {
                    headActive = node;
                    tailActive = node;
                }
                return;
            }
            goto createNew;
        }
        node = node->next;
    }

createNew:
    // Node not found in any list; attempt to allocate
    Node* newNode = allocateNode(id);
    if (newNode != nullptr) {
        if (newNode->flags & 0x20) {
            gGlobalManager.count--;
            newNode->flags &= ~0x20;
        }
        lockList();
        newNode->flags &= ~0x40;
        unlockList();
    }
}