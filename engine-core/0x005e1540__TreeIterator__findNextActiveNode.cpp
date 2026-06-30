// FUNC_NAME: TreeIterator::findNextActiveNode
void TreeIterator::findNextActiveNode(void)
{
    // Offset 0: some iterator state flag (e.g., m_bStarted or m_bValid)
    // Offset 4: pointer to current node (m_pCurrent)
    // Node structure (at offset +0x15: m_bActive, offset +0x0: m_pParent, offset +0x4: m_pNextSibling, offset +0x8: m_pFirstChild)
    // This function advances the iterator to the next active node in a tree traversal.

    if (this->m_bStarted == 0) {
        // Iterator not started; reset/reinitialize
        FUN_00b97aea(); // Likely initializes or resets to beginning
    }
    Node* current = this->m_pCurrent;

    if (current->m_bActive == '\0') {
        // Current node is inactive, need to find next active one
        Node* parent = current->m_pParent; // offset +0x0
        if (parent->m_bActive == '\0') {
            // Parent is also inactive, so drill down from parent's first child
            char childActive = parent->m_pFirstChild->m_bActive; // offset +0x8 of parent
            Node* child = parent->m_pFirstChild;
            while (childActive == '\0') {
                childActive = child->m_pFirstChild->m_bActive;
                child = child->m_pFirstChild;
            }
            this->m_pCurrent = child;
            return;
        }
        // Parent is active, so move to next sibling
        Node* sibling = current->m_pNextSibling; // offset +0x4
        char siblingActive = sibling->m_bActive;
        while (siblingActive == '\0' && this->m_pCurrent == sibling->m_pParent) {
            this->m_pCurrent = sibling;
            sibling = sibling->m_pNextSibling;
            siblingActive = sibling->m_bActive;
        }
        // After loop, check if current is now active (should not be, as we only move when inactive)
        if (this->m_pCurrent->m_bActive != '\0') {
            FUN_00b97aea(); // Error: unexpected active node; reset
            return;
        }
        this->m_pCurrent = sibling;
    } else {
        // Current node is active, move to its first child
        Node* child = current->m_pFirstChild; // offset +0x8
        this->m_pCurrent = child;
        if (child->m_bActive != '\0') {
            FUN_00b97aea(); // Error: child is already active? Reset
            return;
        }
    }
    return;
}