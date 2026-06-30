// FUNC_NAME: LinkedListNode::DestroyNode
// Address: 0x004530e0
// Destructor for a node that may be part of a doubly linked list.
// Removes itself from the list, then clears all subordinate nodes.

void __fastcall LinkedListNode::DestroyNode(void* thisPtr)
{
    // Offsets based on decompilation:
    // +0x00: vtable pointer
    // +0x04: head of a child list (used in loop)
    // +0x18: previous node pointer (prev)
    // +0x1C: next node pointer (next)
    // +0x20: pointer to this node (unused canonical address)

    uint32* this = (uint32*)thisPtr;

    uint32* prev = (uint32*)this[6];  // +0x18
    uint32* next = (uint32*)this[7];  // +0x1C
    uint32* node = (uint32*)this[8];  // +0x20 (should be the same as this)

    if (prev != 0) {
        if (next == 0) {
            // If no next, update previous node's next (offset 4) to point to this node.
            prev[1] = (uint32)node;  // prev[1] is at prev+4
        } else {
            // If next exists, update next node's prev (offset 8) to point to this node.
            next[2] = (uint32)node;  // next[2] is at next+8
        }
        if (node != 0) {
            node[1] = (uint32)next;  // this node's next (offset 4) set to next
        }
    }

    // Set vtable to a global destructor vtable (indicates object is destroyed)
    this[0] = (uint32)&PTR_LAB_00e42de4;

    // Iterate over child list starting at offset 4
    uint32* child = (uint32*)this[1];  // +0x04
    while (child != 0) {
        uint32* nextChild = (uint32*)child[2];  // +0x08 (assumed next pointer in child node)
        child[0] = 0;
        child[1] = 0;
        child[2] = 0;
        child = nextChild;
    }
}