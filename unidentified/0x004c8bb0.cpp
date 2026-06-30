// FUN_004c8bb0: EARSListNode::removeFromList
void __thiscall EARSListNode::removeFromList(void) {
    EARSListNode* pNode;
    EARSListNode* pCurrent;

    pNode = gs_nodeListHead; // global list head pointer
    this->bRemoved = 1; // +0x1c: mark node as removed
    if (pNode != nullptr) {
        if (pNode == this) {
            // This node is the head, remove it
            gs_nodeListHead = nullptr;
            // Check if there's an object to release
            if (this->m_pObject != nullptr) { // +0x14: pointer to associated object
                this->m_pObject = nullptr;
                FUN_005e5080(); // likely object release/destructor
                return;
            }
        } else {
            // Traverse list to find and unlink this node
            while (pNode->m_pNext != nullptr) { // +0x8: next pointer
                pCurrent = pNode->m_pNext;
                if (pCurrent == this) {
                    // Unlink this node
                    pNode->m_pNext = this->m_pNext;
                    // After unlinking, check object release
                    if (this->m_pObject != nullptr) {
                        this->m_pObject = nullptr;
                        FUN_005e5080();
                    }
                    return;
                }
                pNode = pCurrent;
            }
        }
    }
    return;
}