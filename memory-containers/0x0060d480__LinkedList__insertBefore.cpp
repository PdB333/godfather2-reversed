// FUNC_NAME: LinkedList::insertBefore
// Function address: 0x0060d480
// Inserts a new node before the given node in a doubly linked list.
// Uses a global allocator function pointer and context.
// The list head is stored in a global, and count is maintained.

struct ListNode {
    void* data;          // +0x00
    ListNode* pNext;     // +0x04
    ListNode* pPrev;     // +0x08
};

// Global allocator function pointer and context
typedef void* (*AllocFunc)(size_t size, void* context);
extern AllocFunc g_pAllocFunc;          // DAT_012224f0
extern void* g_pAllocContext;           // DAT_012224ec (if null, uses g_defaultAllocContext)
extern void* g_defaultAllocContext;     // DAT_01218a14
extern ListNode* g_pListHead;           // DAT_012224e0
extern unsigned int g_uiListCount;      // DAT_012224e8

// __thiscall: ECX = this (pointer to the node before which we insert)
ListNode** LinkedList::insertBefore(void* dataParam, ListNode** ppOutNode) {
    ListNode* pCurrNode = this;  // this is the node before which we insert (puVar1)
    ListNode* pNewNode;

    // Determine allocator context
    void* allocContext = g_pAllocContext;
    if (allocContext == nullptr) {
        allocContext = g_defaultAllocContext;
    }

    // Allocate a new node (3 fields * 4 bytes)
    pNewNode = (ListNode*)g_pAllocFunc(0xC, allocContext);
    if (pNewNode != nullptr) {
        pNewNode->data = dataParam;   // *unaff_retaddr assumed to be dataParam (likely passed in a register)
        pNewNode->pNext = nullptr;
        pNewNode->pPrev = nullptr;
    }

    // Insert before pCurrNode
    if (pCurrNode == g_pListHead) {
        // Inserting before the head: new node becomes new head
        pNewNode->pPrev = nullptr;
        g_pListHead = pNewNode;
    } else {
        // Insert into middle
        ListNode* pPrevNode = pCurrNode->pPrev;
        pNewNode->pPrev = pPrevNode;
        pPrevNode->pNext = pNewNode;
    }
    pNewNode->pNext = pCurrNode;
    pCurrNode->pPrev = pNewNode;

    // Update count
    g_uiListCount++;

    // Store result in output parameter
    *ppOutNode = pNewNode;
    return ppOutNode;
}