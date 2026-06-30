// FUNC_NAME: ListNode::insertBefore(void* container)
// 0x006d68e0 - Inserts this node before the list head stored at container+0x48.
// Node layout: [0] next pointer, [4] prev pointer (direct, not pointer-to-pointer).
// Assumes node is already removed from any previous list.
int* __thiscall ListNode::insertBefore(int* this, int* container)
{
    // container may be null; if non-null, dereference to get list head node.
    int* listHead = container;
    if (container != 0) {
        listHead = (int*)((char*)container + 0x48);
    }

    // Only re-link if we are not already pointing to this head
    if (this[0] != (int)listHead) {
        if (this[0] != 0) {
            // Remove from current list (unlink this node)
            FUN_004daf90(this);
        }
        // Set this node's next pointer to the list head
        this[0] = (int)listHead;
        if (listHead != 0) {
            // Set this node's prev pointer to the list head's prev
            this[1] = listHead[1];
            // Update list head's prev to point to this node
            listHead[1] = (int)this;
        }
    }
    return this;
}