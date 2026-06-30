// FUNC_NAME: NodeListManager::popAndFreeNode

// Function at 0x004d8dd0
// Pops the head node from the active list and pushes it onto the free list.
// Returns the popped node pointer, or 0 if the active list is empty.
// If the node being removed is the current active node (g_currentActiveNode), it clears that pointer.

// Global pool pointers (static members of NodeListManager or global)
// +0x00: next pointer offset within a Node structure
static int* g_activeListHead = (int*)0x012189fc;   // head of active list
static int* g_freeListHead   = (int*)0x012189f8;   // head of free list (stack)
static int* g_currentActiveNode = (int*)0x01218a00; // pointer to current active node (maybe being iterated)

int NodeListManager::popAndFreeNode()
{
    int node = (int)g_activeListHead;  // node to remove
    int result = 0;

    if (g_activeListHead != 0) {
        int* nextPtr = (int*)((int)g_activeListHead + 0xf0); // next pointer field

        // If this node is the current active node, clear it
        if (g_currentActiveNode == (int*)g_activeListHead) {
            g_currentActiveNode = 0;
        }

        // Advance active list head to next node
        g_activeListHead = (int*)(*nextPtr);

        // Push the node onto the free list (stack)
        *nextPtr = (int)g_freeListHead;   // point removed node to old free list head
        g_freeListHead = (int*)node;      // free list head becomes this node

        result = node;
    }

    // Call subsequent processing (e.g., notify pool that a node was freed)
    FUN_004d8e60();

    return result;
}