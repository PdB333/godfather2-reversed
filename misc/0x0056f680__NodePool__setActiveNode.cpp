// FUNC_NAME: NodePool::setActiveNode

void __fastcall NodePool::setActiveNode(int thisPtr, int newActiveNode) {
    int* oldNode;

    if (newActiveNode != 0) {
        // +0x09: reference count
        *(char*)(newActiveNode + 9) += 1;
    }

    oldNode = *(int**)(thisPtr + 0x38); // +0x38: current active node pointer
    if (oldNode != 0) {
        // Decrement old node's reference count
        *(char*)(oldNode + 9) -= 1;

        // +0x08: locked flag (0 = free)
        if ((*(char*)(oldNode + 8) == 0) && (*(char*)(oldNode + 9) == 0)) {
            int nextNode = *oldNode;         // +0x00: next pointer
            int prevNode = oldNode[1];       // +0x04: prev pointer

            if (nextNode != 0) {
                *(int*)(nextNode + 4) = prevNode; // next->prev = prev
            }

            int* globalList = (int*)0x01205560; // Static free list head structure

            if (prevNode != 0) {
                // Old node was not the head: unlink from list
                *(int*)prevNode = nextNode; // prev->next = next
                *(int*)(thisPtr + 0x38) = newActiveNode;
                return;
            }

            // Old node was the head of the active list; update global free list
            *(int*)((int)globalList + 8) = *(int*)((int)globalList + 4); // +0x08 = old tail
            *(int*)((int)globalList + 4) = nextNode;                     // +0x04 = new tail (next)
            if (nextNode == 0) {
                // List became empty; adjust head/tail pointer
                *(int*)((int)globalList + 8) = *(int*)((int)globalList + 0xc); // +0x0c = end marker
            }
        }
    }

    // Set the new active node
    *(int*)(thisPtr + 0x38) = newActiveNode;
}