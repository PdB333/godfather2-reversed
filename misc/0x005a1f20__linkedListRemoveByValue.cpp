// FUNC_NAME: linkedListRemoveByValue
// Function: 0x005a1f20
// Removes a node with a given value from a global singly linked list.
// Global head pointer at 0x0119a9c8, free function pointer at 0x0119caf4.

struct LinkedListNode {
    int value;    // +0x00
    LinkedListNode* next; // +0x04
};

extern LinkedListNode** g_headPointer;          // DAT_0119a9c8
extern void (*g_freeNode)(LinkedListNode*);     // DAT_0119caf4

void __fastcall linkedListRemoveByValue(int unused, int value) {
    LinkedListNode** ppHead = g_headPointer;
    LinkedListNode* pCurr = *ppHead;
    LinkedListNode* pPrev = nullptr;

    // Check if head node matches
    if (pCurr != nullptr && pCurr->value == value) {
        LinkedListNode* pNewHead = pCurr->next;
        if (g_freeNode)
            g_freeNode(pCurr);
        *ppHead = pNewHead;
        return;
    }

    // Traverse list looking for match
    while (pCurr != nullptr && pCurr->value != value) {
        pPrev = pCurr;
        pCurr = pCurr->next;
    }

    // If found, unlink and free
    if (pCurr != nullptr) {
        pPrev->next = pCurr->next;
        if (g_freeNode)
            g_freeNode(pCurr);
    }
}