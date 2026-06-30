// FUNC_NAME: ListNode::linkBefore
// Function at 0x006906e0: Inserts this node before the embedded node at offset 0x48 of the target object.
// Offsets: this+0x00 = next pointer, this+0x04 = prev pointer; targetObj+0x48 = node with next at +0x00, prev at +0x04.

int* __thiscall ListNode::linkBefore(int* this, int targetObj) {
    int* targetNode;

    // If target object is not null, get the node embedded at offset 0x48
    if (targetObj == 0) {
        targetNode = 0;
    } else {
        targetNode = (int*)(targetObj + 0x48);
    }

    // Only relink if the current next pointer differs
    if (*this != (int)targetNode) {
        // Remove this node from its current list (if any)
        if (*this != 0) {
            FUN_004daf90(this);  // likely unlinkNode(this)
        }

        // Set next pointer to target node
        *this = (int)targetNode;

        if (targetNode != 0) {
            // Set this node's prev to the target's prev
            this[1] = targetNode[1];

            // Update the target's prev to point back to this node
            *(int**)(targetNode + 1) = this;
        }
    }

    return this;
}