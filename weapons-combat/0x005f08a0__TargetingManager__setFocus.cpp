// FUNC_NAME: TargetingManager::setFocus
int __thiscall TargetingManager::setFocus(int id, bool clearOnly) {
    Node* node;

    if (id != 0 && this->enabledCount != 0) {
        // Traverse linked list of nodes
        for (node = this->head; node != nullptr; node = node->next) {
            if (node->data != nullptr && node->data->objectId == id) {
                // Found a node with matching ID
                if (node->isEnabled == '\0') {
                    // Node is disabled – clear focus and abort
                    this->currentId = 0;
                    return 0;
                }
                break;
            }
        }
    }

    // Clear any existing focus
    if (this->currentId != 0) {
        this->currentId = 0;
    }

    // Internal cleanup/update
    this->onFocusChanged();

    // Set new focus if not in clear-only mode
    if (clearOnly == false) {
        this->currentId = id;
    }

    return 1;
}