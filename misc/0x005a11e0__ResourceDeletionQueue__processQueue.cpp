// FUNC_NAME: ResourceDeletionQueue::processQueue
void ResourceDeletionQueue::processQueue(Node** ppHead) {
    Node* pNode = *ppHead;
    while (pNode != nullptr) {
        Node* pCurrent = reinterpret_cast<Node*>(*ppHead); // same as pNode, but code reloads from head
        if (pCurrent != nullptr) {
            Object* pObj = pCurrent->pObject;
            Node* pNext = pCurrent->pNext; // pCurrent[1]
            if (pObj != nullptr) {
                pObj->refCount--; // *pObj = *pObj - 1
                if (pObj->refCount == 0) {
                    Object* pObjCheck = pCurrent->pObject; // reload, same as pObj
                    if (pObjCheck != nullptr) {
                        SubObject* pSub = pObjCheck->pSubObject; // *(+4)
                        if (pSub != nullptr) {
                            pSub->refCount--; // *pSub = *pSub - 1
                            if (pSub->refCount == 0) {
                                SubObject* pSubCheck = pObjCheck->pSubObject; // reload
                                if (pSubCheck != nullptr) {
                                    // Release sub-object resources (e.g., destructor logic)
                                    FUN_005a1b40();
                                    // Deallocate sub-object (size 0x30)
                                    (*g_deallocResource)(pSubCheck, 0x30);
                                }
                            }
                        }
                    }
                    // Deallocate object (size 0x10)
                    (*g_deallocResource)(pObj, 0x10);
                }
            }
            // Deallocate the node (size 0x10) from node-specific pool
            (*g_deallocNode)(pCurrent);
            // Advance head to next node
            *ppHead = pNext;
        }
        pNode = *ppHead;
    }
}

// Helper structure definitions (size assumptions from 0x10 and 0x30)
struct SubObject {
    int refCount;          // +0x00
    // ... (total 0x30 bytes)
};
struct Object {
    int refCount;          // +0x00
    SubObject* pSubObject; // +0x04
    // ... (total 0x10 bytes)
};
struct Node {
    Object* pObject;       // +0x00
    Node* pNext;           // +0x04
    // ... (total 0x10 bytes)
};