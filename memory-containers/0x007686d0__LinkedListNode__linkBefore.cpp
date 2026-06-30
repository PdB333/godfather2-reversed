// FUNC_NAME: LinkedListNode::linkBefore
// Address: 0x007686d0
// Role: Inserts this node into a doubly linked list before a given target node (with embedded linked list node at offset 0x48).
//       If target is null, the node is removed from any list (sets next pointer to null).
//       The node is first removed from its current list via FUN_004daf90 (presumably unlink),
//       then linked as the predecessor of the target node.
//       Returns this for chaining.

int* __thiscall LinkedListNode::linkBefore(int* thisPtr, int* target) {
    // If target is non-null, adjust pointer to point to the embedded list node at offset 0x48
    if (target != 0) {
        target = (int*)((char*)target + 0x48); // +0x48: offset of list node within the owning object
    }
    // Only relink if the target differs from current next pointer
    if (*thisPtr != target) {
        // Remove from current list if already linked
        if (*thisPtr != 0) {
            FUN_004daf90(thisPtr); // unlink node from its current list
        }
        // Set next pointer to target
        *thisPtr = target;
        if (target != 0) {
            // Set this node's prev to the old prev of target
            thisPtr[1] = *(int*)(target + 4); // +4: prev pointer in list node
            // Update target's prev to point to this node
            *(int**)(target + 4) = thisPtr;   // +4: prev pointer in list node
        }
    }
    return thisPtr;
}