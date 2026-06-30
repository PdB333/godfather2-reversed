// FUNC_NAME: IntrusiveList::extractNode
// Address: 0x004cec70
// Extracts a node from an intrusive doubly-linked list and returns an iterator
// (container pointer + next node). Also manages a global free node list.

struct ListNode {
    ListNode* m_pNext;   // +0x00
    ListNode* m_pPrev;   // +0x04
};

struct ListContainer {
    char unknown[0x18];  // padding up to offset 0x18
    ListNode* m_pHead;   // +0x18  sentinel or head node
    int m_nCount;        // +0x1C
};

struct ExtractResult {
    ListContainer* m_pContainer; // +0x00
    ListNode*      m_pNext;      // +0x04
};

// Global free-list manager (EDI-based in original)
extern ListContainer* g_pFreeListManager;

static void assertionError();

void listExtractNode(ExtractResult* pOut, ListContainer* pContainer, ListNode* pNode) {
    ListNode* pNext;

    // Validate container and node
    if (pContainer == nullptr) {
        assertionError();
    }
    if (pNode == pContainer->m_pHead) {
        assertionError();
    }

    pNext = pNode->m_pNext; // remember next node

    // If the node is not the free-list sentinel, remove it from its list
    if (pNode != g_pFreeListManager->m_pHead) {
        // Unlink pNode: update predecessor's next and successor's prev
        pNode->m_pPrev->m_pNext = pNext;        // *(int*)pNode[1] = next
        pNext->m_pPrev = pNode->m_pPrev;        // *(int*)(pNext+4) = pNode[1]
        
        // Call deallocation or some virtual function (size = 0xC)
        (**(void(__thiscall**)(void*, int))*g_pFreeListManager)(pNode, 0xC);
        g_pFreeListManager->m_nCount--;
    }

    // Fill output
    pOut->m_pContainer = pContainer;
    pOut->m_pNext = pNext;
}