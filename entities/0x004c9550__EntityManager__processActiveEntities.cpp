// FUNC_NAME: EntityManager::processActiveEntities
void EntityManager::processActiveEntities(void* updateContext) {
    // Calls some setup/validation function
    FUN_004dafd0(updateContext);

    // +0x10: pointer to list header structure (ListHead)
    ListHead* headStruct = *(ListHead**)(this + 0x10);
    if (!headStruct) {
        return; // Safety – should never happen
    }

    // +0x1c in ListHead: pointer to dummy sentinel node (circular doubly-linked list)
    ListNode* dummyNode = *(ListNode**)((int)headStruct + 0x1c);
    if (!dummyNode) {
        return;
    }

    // First real node is dummy->next (next pointer at offset 0)
    ListNode* currentNode = *(ListNode**)(dummyNode);
    while (currentNode != dummyNode) {
        // Sanity checks – if corrupted, trigger error handler
        if (currentNode == nullptr || currentNode == dummyNode ||
            dummyNode == nullptr) {
            FUN_00b97aea(); // Error: list integrity violation
            break;
        }

        // Process the node (e.g., update state, call AI, etc.)
        FUN_004c8e90();
        FUN_004cab50();

        // Move to next node (next pointer at offset 0 of ListNode)
        currentNode = *(ListNode**)(currentNode);
    }
}