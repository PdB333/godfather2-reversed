// FUNC_NAME: ManagedRef::setTarget
void __thiscall ManagedRef::setTarget(RefCountedNode* newTarget)
{
    // +0x09: refCount
    if (newTarget != 0) {
        newTarget->refCount++;
    }

    RefCountedNode* oldTarget = this->m_pTarget; // +0x38
    if (oldTarget != 0) {
        oldTarget->refCount--;
        // +0x08: active flag (0 = inactive)
        // If refcount drops to zero and object is inactive, remove from global list
        if (oldTarget->activeFlag == 0 && oldTarget->refCount == 0) {
            // Remove node from doubly linked list (global list at DAT_01205560)
            RefCountedNode* oldNext = oldTarget->next;   // +0x00
            RefCountedNode* oldPrev = oldTarget->prev;   // +0x04
            if (oldNext != 0) {
                oldNext->prev = oldPrev;                // unlink this node from next
            }
            GlobalNodeList* list = g_nodeList;           // DAT_01205560
            if (oldPrev != 0) {
                oldPrev->next = oldNext;
                this->m_pTarget = newTarget;
                return;                                  // early exit after reassign
            } else {
                // oldTarget was head: update head and tail
                list->head = list->tail;                 // +0x08 = +0x04
                list->tail = oldNext;                    // +0x04 = oldNext
                if (oldNext == 0) {
                    list->head = list->sentinel;         // +0x0c (sentinel when empty)
                }
            }
        }
    }
    this->m_pTarget = newTarget;
}