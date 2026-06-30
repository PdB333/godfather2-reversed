// FUNC_NAME: Node::insertBefore
// Function at 0x005fdee0: Inserts this node before a given node in an intrusive doubly linked list.
// The list uses a "next" pointer at +0x4c and a "prev" pointer at +0x50 (which points to the address of the previous node's "next" field).
// +0xbc is a state flag set to 2 after insertion.

void __thiscall Node::insertBefore(Node* otherNode) {
    // piVar1 points to this->next (offset +0x4c)
    int** nextPtr = reinterpret_cast<int**>(this + 0x4c);
    
    // Adjust otherNode: if non-null, use its next field address (offset +0x48)
    int* targetNext;
    if (otherNode == nullptr) {
        targetNext = nullptr;
    } else {
        targetNext = reinterpret_cast<int*>(reinterpret_cast<char*>(otherNode) + 0x48);
    }
    
    // If already pointing to the same node, skip unlinking
    if (*nextPtr != targetNext) {
        // Remove from current list if already linked
        if (*nextPtr != nullptr) {
            unlinkNode(nextPtr); // FUN_004daf90 - removes node from list
        }
        // Set this->next to targetNext
        *nextPtr = targetNext;
        if (targetNext != nullptr) {
            // Set this->prev to the previous node's next pointer (stored at targetNext+4)
            // targetNext+4 is the "prev" field of the node we are inserting before
            *(reinterpret_cast<int*>(this + 0x50)) = *(targetNext + 4);
            // Update the previous node's next pointer to point to this->next
            *(targetNext + 4) = nextPtr;
        }
    }
    // Mark node as inserted (state = 2)
    *(reinterpret_cast<int*>(this + 0xbc)) = 2;
}