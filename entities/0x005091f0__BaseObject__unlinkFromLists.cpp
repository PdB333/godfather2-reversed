// FUNC_NAME: BaseObject::unlinkFromLists
void __thiscall BaseObject::unlinkFromLists() {
    // Class layout (assuming 4-byte pointers):
    // +0x00: vtable pointer
    // +0x04: ?? 
    // +0x08: ??
    // +0x0C: list1_node.next  (pointer to next in list1)
    // +0x10: list1_node.prev  (pointer to prev in list1, or pointer to the field that points to this node)
    // +0x14: list2_node.next
    // +0x18: list2_node.prev

    // Assume list1_node is an intrusive linked list node with next at +0x0C, prev at +0x10.
    // List2_node at +0x14, +0x18.

    // Remove from first list (anchored at offset 0x0C)
    int* nextNode = *(int**)((char*)this + 0x0C); // list1_node.next
    if (nextNode != nullptr) {
        int* prevPtr = *(int**)((char*)nextNode + 0x04); // list1_node.prev of the next node
        if (prevPtr == (int*)((char*)this + 0x0C)) {
            // Common case: next node's prev points directly to our node
            *(int**)((char*)nextNode + 0x04) = *(int**)((char*)this + 0x10); // update next node's prev to our prev
        } else {
            // Walk the list backwards to find the node that points to us
            int* walker = prevPtr;
            int* nextWalker = (int*)walker[1]; // walker->prev (since walker is a node, +4 is its prev)
            while (nextWalker != (int*)((char*)this + 0x0C)) {
                walker = nextWalker;
                nextWalker = (int*)walker[1];
            }
            // found the predecessor: set its prev to our prev (i.e., unlink)
            walker[1] = *(int*)((char*)this + 0x10);
        }
    }

    // Remove from second list (anchored at offset 0x14)
    nextNode = *(int**)((char*)this + 0x14); // list2_node.next
    if (nextNode != nullptr) {
        int* prevPtr = *(int**)((char*)nextNode + 0x04); // list2_node.prev of the next node
        if (prevPtr == (int*)((char*)this + 0x14)) {
            // Common case: next node's prev points directly to our node
            *(int**)((char*)nextNode + 0x04) = *(int**)((char*)this + 0x18); // update next node's prev to our prev
            // Then set vtable to base vtable and return
            *(void***)this = (void**)&PTR_LAB_00e3729c; // BaseObject vtable
            return;
        } else {
            // Walk backwards
            int* walker = prevPtr;
            int* nextWalker = (int*)walker[1]; // walker->prev
            while (nextWalker != (int*)((char*)this + 0x14)) {
                walker = nextWalker;
                nextWalker = (int*)walker[1];
            }
            walker[1] = *(int*)((char*)this + 0x18);
        }
    }

    // Set vtable to base vtable
    *(void***)this = (void**)&PTR_LAB_00e3729c;
}