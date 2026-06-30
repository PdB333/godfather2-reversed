// FUNC_NAME: ListNode::attachToOwner
int * __thiscall ListNode::attachToOwner(int *this, int *owner)
{
    // owner is a pointer to a parent object that contains a list head at offset 0x48
    // and a list tail (or prev pointer) at offset 0x4C
    int *listHead;
    
    if (owner == 0) {
        listHead = 0;
    } else {
        listHead = (int *)((char *)owner + 0x48); // +0x48: pointer to first child node
    }
    
    // If this node is already attached to a different owner, detach it first
    if (this[0] != (int)listHead) {
        if (this[0] != 0) {
            // Detach from current owner (FUN_004daf90 likely removes from list)
            FUN_004daf90(this);
        }
        this[0] = (int)listHead; // store pointer to owner's list head (or sentinel)
    }
    
    if (listHead != 0) {
        // Insert this node into the owner's doubly linked list
        // this[1] is the "prev" pointer; listHead[1] is the owner's "tail" pointer
        this[1] = listHead[1]; // this->prev = owner->tail
        listHead[1] = (int)this; // owner->tail = this
        // Note: The "next" pointer of this node is already set to listHead (the head pointer)
        // This appears to be a circular or sentinel-based list where the head node
        // also serves as the sentinel, and insertion is at the end.
    }
    
    return this;
}