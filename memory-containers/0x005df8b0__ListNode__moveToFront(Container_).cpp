// FUNC_NAME: ListNode::moveToFront(Container*)
void __thiscall ListNode::moveToFront(int node, int container) {
    int* nextNodePtr; // pointer to the next node (node->next)
    int* prevNodePtr; // pointer to the previous node (node->prev)

    // Save the current next pointer of this node (offset +0x8)
    nextNodePtr = *(int**)(node + 8);

    // Remove this node from its current position by pointing node->next to nextNodePtr->next
    // Actually: node->next = nextNodePtr->next
    *(int*)(node + 8) = *nextNodePtr;
    if (*(char*)(*nextNodePtr + 0x15) == '\0') {
        // If some condition on the original next node, update its prev (offset +0x4)
        *(int*)(*nextNodePtr + 4) = node;
    }
    // Adjust the next node's prev to point back to this node (piVar1[1] = node->prev)
    nextNodePtr[1] = *(int*)(node + 4);

    // Check if this node is the tail (container->head->prev == node)
    if (node == **(int**)(container + 0x1c + 4)) { // container+0x1c points to head, head+4 is tail
        // Update tail to point to nextNodePtr
        *(int**)(*(int*)(container + 0x1c) + 4) = nextNodePtr;
        *nextNodePtr = node;
        *(int**)(node + 4) = nextNodePtr;
        return;
    }

    // Save the previous node of this node
    prevNodePtr = *(int**)(node + 4);
    // If this node is the head (node->prev->next == node)
    if (node == *prevNodePtr) {
        // Update head's next to skip this node
        *prevNodePtr = (int)nextNodePtr;
        *nextNodePtr = node;
        *(int**)(node + 4) = nextNodePtr;
        return;
    }

    // Normal case: update previous node's next, then place this node after nextNodePtr
    prevNodePtr[2] = (int)nextNodePtr;
    *nextNodePtr = node;
    *(int**)(node + 4) = nextNodePtr;
    return;
}