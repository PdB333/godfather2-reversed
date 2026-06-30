// FUNC_NAME: CNodeList::getNodeAtIndex
// Function at 0x0045f2a0: Retrieve a node by index from a linked list and perform actions.
void __thiscall CNodeList::getNodeAtIndex(int nodeIndex) {
    // this->m_pList at +0x218: pointer to list header structure
    if (this->m_pList != nullptr) {
        if (nodeIndex >= 0) {
            // m_pList->m_pHead at +0x124: first node in the linked list
            CNode* currentNode = this->m_pList->m_pHead;
            int count = 0;
            // Walk the list up to nodeIndex (or until null is reached)
            while (count < nodeIndex) {
                // Each node has a next pointer at +0x124
                currentNode = currentNode->m_pNext;
                if (currentNode == nullptr) {
                    goto afterProcessing;
                }
                count++;
            }
            // If node at index exists, process it
            if (currentNode != nullptr) {
                processFoundNode(); // FUN_00572580
            }
        }
afterProcessing:
        // Always call this after the retrieval attempt
        processResult(); // FUN_00572830
    }
}