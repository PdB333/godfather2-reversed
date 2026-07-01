// FUNC_NAME: SomeManager::setHeadNode
void __thiscall SomeManager::setHeadNode(int this, int pNode) {
    int* headPtr = (int*)(this + 0x1e40); // +0x1e40: m_pHead (pointer to head node)
    int newHead;

    // If removing head (pNode == 0) and current head is valid (non-zero and not sentinel 0x48)
    if ((pNode == 0) && (*headPtr != 0) && (*headPtr != 0x48)) {
        *(int*)(this + 0x858) = 4; // +0x858: m_state (set to 4, e.g., idle)
    }

    // Convert pNode to actual node pointer: if non-zero, add 0x48 (node offset within container?)
    if (pNode == 0) {
        newHead = 0;
    } else {
        newHead = pNode + 0x48;
    }

    if (*headPtr != newHead) {
        if (*headPtr != 0) {
            FUN_004daf90(headPtr); // Remove old head node (function likely deletes or unlinks)
        }
        *headPtr = newHead; // Set new head
        if (newHead != 0) {
            // Copy the next pointer of the new head node to this+0x1e44 (m_pHeadNext)
            *(int*)(this + 0x1e44) = *(int*)(newHead + 4);
            // Set the new head node's next pointer to point to the head pointer's address (intrusive list pattern)
            *(int**)(newHead + 4) = headPtr;
        }
    }
}