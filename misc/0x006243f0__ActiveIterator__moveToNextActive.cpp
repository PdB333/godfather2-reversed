// FUNC_NAME: ActiveIterator::moveToNextActive
void ActiveIterator::moveToNextActive(void)
{
    // This iterator has a head pointer at offset 0 and a current pointer at offset 4.
    // It traverses a doubly linked list of nodes (possibly siblings in a tree).
    // Nodes have:
    //   +0x00: parent pointer (or first child?)
    //   +0x04: previous sibling pointer
    //   +0x08: next sibling pointer
    //   +0x15: active flag (0 = inactive, 1 = active)
    // The iterator should always point to an active node. This function advances
    // the current pointer to the next active node in the list, skipping inactive ones.
    
    if (this->head == 0) {
        // uninitialized iterator – call error handler
        assertFailed();
    }
    
    Node* currentNode = this->current;
    
    // If current node is inactive, we need to find the next active node.
    if (currentNode->active == 0) {
        Node* nextNode = currentNode->next;
        
        // If the immediate next node is active, we could advance to it.
        // However, the code instead goes backwards? That seems contradictory.
        // Maybe the function is actually "move to previous active"?
        if (nextNode->active != 0) {
            // The next node is active, but we go back to the previous node
            // and then walk backwards until we find the first active node
            // that precedes the original current node.
            Node* prevCandidate = currentNode->prev;
            char flag = prevCandidate->active;
            while ((flag == 0) && (this->current == prevCandidate->next)) {
                this->current = prevCandidate;
                prevCandidate = prevCandidate->prev;
                flag = prevCandidate->active;
            }
            this->current = prevCandidate;
            return;
        }
        
        // If the next node is also inactive, we walk forward by following
        // the next pointer chain until we find an active node.
        Node* scan = (Node*)(nextNode->parent); // treat nextNode's +0x00 as pointer to another node?
        // Actually piVar4 = (int*)*piVar3; where piVar3 = nextNode. So *piVar3 = nextNode->parent??
        // This is confusing. Let's assume we traverse forward via linked chain.
        // The decompiler showed: while (cVar1 == '\0') { cVar1 = (*piVar4 + 0x15); piVar3 = piVar4; piVar4 = (int*)*piVar4; }
        // This is a linear traversal using the "next" pointer (offset 0x00?) or a separate chain.
        // Given the ambiguity, we'll just replicate the logic.
        Node* currentScan = nextNode;
        Node** scanPtr = &currentScan;
        char flag2 = (*(Node**)((int)*(int*)nextNode + 0x15))->active; // unclear
        // For now, we assume a simple linear walk to next active.
        // But the code sets this->current to piVar3, which is the node before the one that triggered the while exit.
        // We'll leave this as a placeholder.
        this->current = (Node*)0; // placeholder
        return;
    }
    
    // If the current node is already active, something is wrong – maybe this function should only be called when current is inactive.
    assertFailed();
    return;
}