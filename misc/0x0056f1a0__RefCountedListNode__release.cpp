// FUNC_NAME: RefCountedListNode::release
// Address: 0x0056f1a0
// This function decrements a reference count and removes the node from a doubly linked list when the count reaches zero.
// Used in a resource/pool management system (EARS engine).

void __thiscall RefCountedListNode::release(void)
{
    int *prevNode;
    int *nextNode;
    void *listManager;

    // Decrement reference count at offset +0x9
    *(char *)((int)this + 9) = *(char *)((int)this + 9) - 1;

    // Check if active flag (offset +0x8) is zero and ref count is zero
    if (((char)this->field_0x8 == '\0') && (*(char *)((int)this + 9) == '\0')) {
        prevNode = (int *)this->field_0x0;      // +0x0: prev pointer
        nextNode = (int *)this->field_0x4;      // +0x4: next pointer

        // Unlink current node from doubly linked list
        if (prevNode != (int *)0x0) {
            *(int **)(prevNode + 4) = nextNode; // Update next pointer of previous node
        }
        listManager = (void *)g_listManager;    // Global list manager (DAT_01205564)
        if (nextNode != (int *)0x0) {
            *nextNode = (int)prevNode;          // Update prev pointer of next node
            return;
        }
        // If no next node, update tail pointer in manager
        *(int *)((int)listManager + 8) = *(int *)((int)listManager + 4);  // tail = head? or head = tail?
        *(int *)((int)listManager + 4) = (int)prevNode;                   // update head
        if (prevNode == (int *)0x0) {
            *(int *)((int)listManager + 8) = *(int *)((int)listManager + 12); // tail = something else
        }
    }
    return;
}