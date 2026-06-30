// FUNC_NAME: SimManager::updateAllComponents
void SimManager::updateAllComponents(float deltaTime)
{
    // FUN_004dafd0 likely begins the update cycle (e.g., reset dirty flags)
    this->beginUpdate(deltaTime);

    // +0x10: pointer to a linked list sentinel node (or head of the active list)
    int* container = *(int**)(this + 0x10);
    // +0x1c within container: offset to the "next" pointer of the sentinel
    // The sentinel itself is a node; its next points to the first real element.
    int* currentNode = *(int**)(container + 0x1c);
    int* sentinel = container; // Container's address used as end marker

    while (true) {
        // Re-read the sentinel's next pointer each iteration (may change if list is modified)
        int* end = *(int**)(*(int*)(this + 0x10) + 0x1c);
        // Debug assertion: validate that the container pointer hasn't changed
        if (currentNode == nullptr || currentNode != *(int**)(this + 0x10)) {
            DEBUG_ASSERT();
        }
        if (currentNode == end) break;

        // Each node has a next pointer at offset 0x1c
        if (currentNode == nullptr) {
            DEBUG_ASSERT();
        }
        if (currentNode == *(int**)(currentNode + 0x1c)) {
            DEBUG_ASSERT(); // Self-loop check
        }

        // Process the current node (e.g., call update and render functions)
        this->processNode(currentNode);   // FUN_004c8e90
        this->postProcessNode(currentNode); // FUN_004cab50

        // Move to next node in the list (offset 0x1c is the next pointer)
        currentNode = *(int**)(currentNode + 0x1c);
    }
}