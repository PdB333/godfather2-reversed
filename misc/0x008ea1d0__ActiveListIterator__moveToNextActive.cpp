// FUNC_NAME: ActiveListIterator::moveToNextActive
void __thiscall ActiveListIterator::moveToNextActive(ActiveListIterator* thisPtr) {
    // thisPtr points to an iterator struct:
    // +0x00: Node* head (root of list)
    // +0x04: Node* current (current node)
    // Node layout:
    // +0x00: Node* next
    // +0x04: Node* prev
    // +0x08: Node* parentOrListHead
    // +0x25: char activeFlag (0 = inactive, non-zero = active)

    Node* head = thisPtr->head;
    if (head == nullptr) {
        // likely assert/error
        assertFail();
    }

    Node* cur = thisPtr->current;
    if (cur->activeFlag == 0) {
        // Current node is inactive; look for next active node
        Node* parent = cur->parentOrListHead; // +0x08
        if (parent->activeFlag != 0) {
            // Parent is active, move backward through siblings until we find an active one
            // But only while still under this parent (parentOrListHead of previous matches current)
            Node* prev = cur->prev; // +0x04
            while ((prev->activeFlag == 0) && (thisPtr->current == prev->parentOrListHead)) {
                thisPtr->current = prev;
                prev = prev->prev;
            }
            thisPtr->current = prev;
            return;
        } else {
            // Parent inactive, move forward through children of parent (parent->next chain)
            Node* child = parent->next; // +0x00
            Node* next = child;
            while (child->activeFlag == 0) {
                child = child->next;
                next = child;
            }
            thisPtr->current = child;
            return;
        }
    }
    // Current already active, error?
    assertFail();
}