// FUNC_NAME: SimManager::updateActiveEntities
bool SimManager::updateActiveEntities(void* thisPtr)
{
    // thisPtr+0x08: pointer to entity list container
    void* container = *(void**)((int)thisPtr + 0x08);
    bool foundInactive = false;

    if (container == nullptr) {
        foundInactive = true;
    } else {
        // container+0x1c: pointer to head node (circular linked list)
        // First node is head->next
        void* currentNode = **(void***)((int)container + 0x1c);
        void* headNode = *(void**)((int)container + 0x1c);

        while (true) {
            // Sanity checks (debug assertions)
            if (container == nullptr) {
                assertFailed(); // FUN_00b97aea
            }
            if (container != *(void**)((int)thisPtr + 0x08)) {
                assertFailed();
            }
            if (currentNode == headNode) break; // Reached end of circular list

            if (container == nullptr) {
                assertFailed();
            }
            if (currentNode == *(void**)((int)container + 0x1c)) {
                assertFailed();
            }

            // Check entity's active flag at offset 0x10
            if (*(int*)((int)currentNode + 0x10) == 0) {
                foundInactive = true;
                processEntity(currentNode); // FUN_005e09e0 (cleanup/remove)
            } else {
                updateEntity(currentNode);  // FUN_005dd660
                processEntity(currentNode); // FUN_005e09e0
            }

            // Move to next node (decompiler omitted this update)
            // currentNode = *(void**)((int)currentNode + 0x1c); // next pointer at offset 0x1c
        }
    }
    return !foundInactive; // true if all entities were active
}