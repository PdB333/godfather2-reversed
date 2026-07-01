// FUNC_NAME: GenericList::clearAndFreeNodes
// Address: 0x008eb9c0
// Role: Clears a doubly-linked list, freeing all nodes and their associated resources at offset +0x20 (node + 8 words).

class GenericListNode {
public:
    GenericListNode* pNext;       // +0x00
    GenericListNode* pPrev;       // +0x04
    void* pResource;              // +0x08  (pointer to some resource that may need cleanup)
    // ... (node size >= 0x24? 0x20 + 4? Actually pResource is at offset 0x20 because int* piVar2, piVar2[8] is offset 0x20)
};

class GenericList {
private:
    GenericListNode* pHead;       // +0x4C
    GenericListNode* pTail;       // +0x50
    // ... (other members)
public:
    void clearAndFreeNodes();     // 0x008eb9c0
};

void GenericList::clearAndFreeNodes()
{
    GenericListNode* pNode = this->pHead;
    while (pNode != nullptr) {
        GenericListNode* pCurrent = this->pHead;  // same as pNode
        GenericListNode* pNext = pCurrent->pNext;
        this->pHead = pNext;
        if (pNext == nullptr) {
            this->pTail = nullptr;
        } else {
            pNext->pPrev = nullptr;
            pCurrent->pNext = nullptr;
        }
        // Free the resource if it exists
        if (pCurrent->pResource != nullptr) {
            freeResource(pCurrent->pResource);  // FUN_004daf90
        }
        freeNode(pCurrent);  // FUN_009c8eb0
        pNode = this->pHead;
    }
}

// Note: freeResource and freeNode are external functions whose symbols are not known.
// The actual function calls have been replaced with stubs.