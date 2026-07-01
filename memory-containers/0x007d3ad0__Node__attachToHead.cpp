// FUNC_NAME: Node::attachToHead
// Function at 0x007d3ad0: Attaches this node to a linked list head located at offset 0x48 in the container object.
// param_2 is a pointer to the container object (e.g., a list owner). The actual list head is at param_2 + 0x48.
// The node's first field (this[0]) stores the container pointer (or list head pointer).
// The node's second field (this[1]) is the next pointer.
// The list head's next pointer is at head + 4.
// If the node is already attached to a different list, it is removed first via FUN_004daf90 (Node::removeFromList).

int* __thiscall Node::attachToHead(int* thisPtr, int* container) {
    int* listHead;
    if (container == 0) {
        listHead = 0;
    } else {
        listHead = container + 0x48; // offset of list head within container
    }
    if (thisPtr[0] != listHead) {
        if (thisPtr[0] != 0) {
            Node::removeFromList(thisPtr); // FUN_004daf90
        }
        thisPtr[0] = listHead; // store list head pointer
        if (listHead != 0) {
            thisPtr[1] = *(int*)(listHead + 4); // set next to head's next
            *(int**)(listHead + 4) = thisPtr; // head's next = this
        }
    }
    return thisPtr;
}