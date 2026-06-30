// FUNC_NAME: ResourcePool::setCurrentItem
void __fastcall ResourcePool::setCurrentItem(void* this, /*ecx*/ Node* newNode) // param_1 is likely this pointer (unaff_ESI)
{
    // Increment ref counter on new item
    if (newNode != nullptr) {
        newNode->refCount++; // +0x9
    }

    Node* oldNode = this->m_pCurrentItem; // +0x44
    if (oldNode != nullptr) {
        // Decrement ref counter on old item
        oldNode->refCount--; // +0x9

        // If old item is no longer active and ref count reached zero, unlink it from the free list
        if (oldNode->activeFlag == 0 && oldNode->refCount == 0) {
            int* nextPtr = oldNode->next; // +0x0
            int* prevPtr = oldNode->prev; // +0x4

            // Remove from doubly linked list
            if (nextPtr != nullptr) {
                *(int*)(nextPtr + 4) = prevPtr; // next->prev = prev
            }

            int* globalHead = g_pFreeListHead; // DAT_0120555c
            if (prevPtr != nullptr) {
                // Non-head node: just link prev to next
                *prevPtr = nextPtr; // prev->next = next
                this->m_pCurrentItem = newNode;
                return;
            }

            // Old node was the head of the free list; update global head/tail
            *(undefined4*)(globalHead + 8) = *(undefined4*)(globalHead + 4); // tail = old head?
            *(int*)(globalHead + 4) = nextPtr; // head = next
            if (nextPtr == nullptr) {
                // List became empty; update tail from some other field
                *(undefined4*)(globalHead + 8) = *(undefined4*)(globalHead + 0xC);
            }
        }
    }

    this->m_pCurrentItem = newNode;
}