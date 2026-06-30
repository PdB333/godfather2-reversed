// FUNC_NAME: List::contains
// Address: 0x006aed40
// This function traverses an intrusive singly linked list embedded in the class.
// The list uses a sentinel node at offset +0x154 from 'this'. The sentinel's next pointer
// is stored at +0x1a4 (sentinel + 0x50). Each list node has a 'next' field at offset +0x50
// which points to the next node's 'next' field (i.e., the address of the next node's next pointer).
// To get the node object, subtract 0x50 from its 'next' pointer.
// The list is terminated when the next pointer points back to the sentinel's 'next' field,
// which after subtraction yields the sentinel address (+0x154).

bool __thiscall List::contains(int param_2) {
    // +0x1a4: pointer to sentinel's next field (or null if empty)
    int* headNext = *(int**)(this + 0x1a4);
    // Sentinal address (only relevant if list non-empty)
    int sentinelAddr = (headNext == nullptr) ? 0 : (int)(this + 0x154);
    // First node: convert from sentinel's next pointer to actual node address
    int currentNode = (headNext == nullptr) ? 0 : (int)headNext - 0x50;

    // Empty list check: both current and sentinel are 0
    if (currentNode == sentinelAddr) {
        return false;
    }

    do {
        // Check condition on the current node (passing param_2 as argument)
        if (FUN_006b7660(param_2) != '\0') {
            return true;
        }
        // Read next pointer from the current node (+0x50)
        int nextPtr = *(int*)(currentNode + 0x50);
        // Convert to next node; if nextPtr is null, treat as 0
        currentNode = (nextPtr == 0) ? 0 : nextPtr - 0x50;
    } while (currentNode != sentinelAddr);

    return false;
}