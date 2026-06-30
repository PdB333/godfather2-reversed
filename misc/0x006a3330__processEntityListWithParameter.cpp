// FUNC_NAME: processEntityListWithParameter
// Function address: 0x006a3330
// Role: Initializes a temporary linked list, processes entries with a parameter, then cleans up the list.
// Known usage: Collects entities/objects matching criteria and applies an operation.
// Struct ListNode assumed to be a doubly linked list node with next and prev pointers (each 4 bytes).

int processEntityListWithParameter(int param) {
    // Sentinel node for doubly linked list (self-referential initialization)
    ListNode localHead;
    localHead.next = &localHead;
    localHead.prev = &localHead;

    // Initialize the list (likely queries some game state to populate)
    int result = initializeList(&localHead); // FUN_006a2d70
    if (result == 0) {
        // Process each entry with the given parameter
        result = processListEntries(&localHead, param); // FUN_006a2e80
    }

    // Cleanup: free all nodes except the sentinel
    ListNode* current = localHead.next;
    while (current != &localHead) {
        ListNode* next = current->next;
        freeNode(current); // FUN_009c8f10
        current = next;
    }

    return result;
}