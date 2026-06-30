// FUNC_NAME: PriorityQueue::recycleHighestPriorityNode

#include <cstdint>

// Assuming this class manages a doubly linked list of nodes, each containing a sub-list of elements with priority.
class PriorityQueue {
public:
    // Offsets relative to this (implicit ECX parameter)
    // +0x04: Node* m_pHead
    // +0x0c: Node* m_pTailSentinel
    // +0x474: Node* m_pFreeList

    struct Node {
        // +0x14: Element* m_pSubListHead
        // +0x1c: Element* m_pSubListTail
        // +0x2c: Node* m_pNextNode
    };

    struct Element {
        // +0x14: float m_fPriority
        // +0x40: Element* m_pPrev
        // +0x44: Element* m_pNext
    };

    int32_t recycleHighestPriorityNode(Element* pProtectedElement);
};

// Global constant – lowest possible float (e.g., -FLT_MAX)
extern const float g_fLowestPriority = -3.40282347e+38f;

int32_t PriorityQueue::recycleHighestPriorityNode(Element* pProtectedElement)
{
    Node* pCurrent = this->m_pHead;   // +0x04
    Node* pBestNode = nullptr;         // iVar3
    float fBestPriority = g_fLowestPriority; // DAT_00e2eff4

    if (pCurrent == this->m_pTailSentinel) // +0x0c
    {
        return 0; // Empty list
    }

    do {
        float fPriority = g_fLowestPriority;
        Element* pSubHead = pCurrent->m_pSubListHead; // +0x14
        Element* pSubTail = pCurrent->m_pSubListTail; // +0x1c

        if (pSubHead != pSubTail) {
            // Sub-list is non-empty; get priority of first element
            fPriority = pSubHead->m_fPriority; // +0x14 of element
        }

        if (fBestPriority < fPriority) {
            fBestPriority = fPriority;
            pBestNode = pCurrent;
        }

        pCurrent = pCurrent->m_pNextNode; // +0x2c
    } while (pCurrent != this->m_pTailSentinel);

    if (pBestNode == nullptr) {
        return 0;
    }

    Element* pVictim = pBestNode->m_pSubListHead; // +0x14
    if (pVictim == pBestNode->m_pSubListTail || pVictim == pProtectedElement) {
        return 0; // Sub-list empty or victim is protected
    }

    // Remove pVictim from the sub-list (doubly linked)
    Element* pPrev = pVictim->m_pPrev; // +0x40
    Element* pNext = pVictim->m_pNext; // +0x44

    pPrev->m_pNext = pNext;   // +0x44 of prev = pNext's offset? Actually write to prev+0x44
    pNext->m_pPrev = pPrev;   // +0x40 of next = pPrev

    // Call virtual destructor on pVictim (vtable+4)
    (*(void(__thiscall**)(Element*))(*(uint32_t*)pVictim + 4))(pVictim);

    // Add pVictim to the free list (singly linked via +0x40)
    pVictim->m_pPrev = this->m_pFreeList; // +0x40
    this->m_pFreeList = pVictim;          // +0x474

    return 1;
}