// FUNC_NAME: PriorityQueue::updateNodePriority
void __thiscall PriorityQueue::updateNodePriority(int nodeId, float newPriority)
{
    // this +0x4c: head pointer of the sorted linked list
    // this +0x68: critical section for thread safety
    // Node structure:
    //   +0x00: next pointer
    //   +0x04: prev pointer
    //   +0xac (0x2b*4): node ID
    //   +0xb0 (0x2c*4): count/flag, if >0 skip reprioritization
    //   +0xb4 (0x2d*4): priority (float)

    int *head = (int *)(this + 0x4c);
    int *node = (int *)*head;
    if (node == nullptr)
        return;

    // Find the node with the specified ID
    while (node[0x2b] != nodeId) {
        node = (int *)*node; // next node
        if (node == nullptr)
            return;
    }

    // If the node has a non-zero count/flag, do nothing
    if (node[0x2c] > 0)
        return;

    // If priority hasn't changed, do nothing
    if (*(float *)&node[0x2d] == newPriority)
        return;

    // Determine the direction of traversal and find insertion point
    if (newPriority <= *(float *)&node[0x2d]) {
        // New priority is less or equal: move forward (next pointers)
        int *insertionPoint = (int *)*node;
        int *curr = insertionPoint;
        if (curr == nullptr) {
            goto updatePriority;
        }
        do {
            if (*(float *)&curr[0x2d] <= newPriority)
                break;
            curr = (int *)*curr;
        } while (curr != nullptr);
        if (curr == insertionPoint) {
            goto updatePriority;
        }
        // Lock and remove/insert in the forward direction
        EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x68));
        lockListForModification(); // FUN_004d1ea0 - acquire internal list manipulation lock
        if (curr == nullptr) {
            insertBeforeHead(); // FUN_004d1e40 - insert node before head
        } else {
            insertBeforeNode(curr); // FUN_004d1e60 - insert node before curr
        }
    } else {
        // New priority is greater: move backward (prev pointers)
        int *insertionPoint = (int *)node[1];
        int *curr = insertionPoint;
        if (curr == nullptr) {
            goto updatePriority;
        }
        do {
            if (curr[0x2c] > 0 || newPriority <= *(float *)&curr[0x2d])
                break;
            curr = (int *)curr[1]; // prev pointer is at +0x04
        } while (curr != nullptr);
        if (curr == insertionPoint) {
            goto updatePriority;
        }
        // Lock and remove/insert in the backward direction
        EnterCriticalSection((LPCRITICAL_SECTION)(this + 0x68));
        lockListForModification(); // FUN_004d1ea0
        if (curr == nullptr) {
            insertAfterTail(); // FUN_004d1e20 - append to tail
        } else {
            insertAfterNode(curr); // FUN_004d1e80 - insert after curr
        }
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(this + 0x68));

updatePriority:
    // Update the priority of the node
    *(float *)&node[0x2d] = newPriority;
    return;
}