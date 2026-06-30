// FUNC_NAME: Animated::setCurrentAnimation
void __thiscall Animated::setCurrentAnimation(int this, char enable, int animationData)
{
    // +0x60: pointer to current animation node (head of list)
    int *headPtr = (int *)(this + 0x60);
    if (enable == '\0') {
        // Disable: clear active flag, remove current node
        *(byte *)(this + 0x8a) &= 0xfe; // clear bit 0 (active/playing flag)
        if (*headPtr != 0) {
            unlinkNode(headPtr); // remove node from list (FUN_004daf90)
            *headPtr = 0;
            return;
        }
    }
    else {
        // Enable: set active flag, possibly switch to new node
        *(byte *)(this + 0x8a) |= 1; // set bit 0
        int newNode;
        if (animationData == 0) {
            newNode = 0;
        }
        else {
            newNode = animationData + 0x48; // offset to animation node within data
        }
        if (*headPtr != newNode) {
            if (*headPtr != 0) {
                unlinkNode(headPtr);
            }
            *headPtr = newNode;
            if (newNode != 0) {
                // Save the node's original next pointer into this+0x64
                // Then set node->next to point to the head pointer location
                // (creates a circular intrusive list)
                *(int *)(this + 0x64) = *(int *)(newNode + 4); // +0x64: saved next?
                *(int **)(newNode + 4) = headPtr; // node->next = &head
            }
        }
    }
}