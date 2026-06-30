// FUNC_NAME: ObjectManager::CheckListAndReturnStatus
// Address: 0x006a30c0 - Checks if a global list is empty and returns a global status value.

// Global state
extern int g_iListStatus;          // DAT_00e50c7c - some status/flag (non-zero indicates list is "ready")
extern void* g_pListSentinel;      // PTR_LOOP_00e50c80 - sentinel node (points to itself when empty)

// ListNode structure (intrusive linked list)
struct ListNode {
    ListNode* next; // +0x00
    ListNode* prev; // +0x04
};

int ObjectManager::CheckListAndReturnStatus(bool* outHasObjects)
{
    if (g_iListStatus != 0) {
        // Manager/wrapper already exists; treat list as empty.
        *outHasObjects = false;
        return g_iListStatus;
    }

    // Count nodes in the circular linked list.
    int nodeCount = 0;
    ListNode* pCurrent = static_cast<ListNode*>(g_pListSentinel);
    // Sentinel address: &g_pListSentinel (the address of the global variable itself)
    ListNode* sentinel = reinterpret_cast<ListNode*>(&g_pListSentinel);

    if (pCurrent != sentinel) {
        do {
            pCurrent = pCurrent->next;
            ++nodeCount;
        } while (pCurrent != sentinel);
    }

    *outHasObjects = (nodeCount != 0);
    return g_iListStatus;
}