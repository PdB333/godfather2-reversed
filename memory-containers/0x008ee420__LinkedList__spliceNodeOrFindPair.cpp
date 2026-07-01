// FUNC_NAME: LinkedList::spliceNodeOrFindPair
// Address: 0x008EE420
// Role: Internal helper for doubly linked list operations. Splices out a node and returns its successor,
//        or finds a node pair during iteration. Parameters 3 and 5 must equal 'this' (debug assert).
// Structure: this+0 = ???, this+4 = pointer to head node pointer (int**), this+8 = ???
//            Node offsets: +0 = prev, +4 = next, +8 = ??? (self-loop if sentinel)
void __thiscall LinkedList::spliceNodeOrFindPair(void* this, int* outPair, void* list1, int* node1, void* list2, int* node2)
{
    int* headNodePtr;
    int local[2]; // unused? Actually used as local_8 in decompiler

    headNodePtr = *(int**)((char*)this + 4);  // deref pointer to get the actual head node pointer

    if (list1 == 0 || list1 != this) {
        // assert failure
        FUN_00b97aea();
    }
    if (node1 == headNodePtr) {
        // node1 is the sentinel head: unlink it
        // First, call something on the node's next field (offset +4)
        FUN_008ed090(*(undefined4*)(*(int*)((char*)this + 4) + 4));
        // Update the next pointer of the node at this+4 to point to itself? (makes circular)
        *(int*)(*(int*)((char*)this + 4) + 4) = *(int*)((char*)this + 4);
        // Clear something at this+8
        *(undefined4*)((char*)this + 8) = 0;
        // Update prev pointer of node at this+4 to point to itself? (circular)
        *(undefined4*)*(undefined4*)((char*)this + 4) = *(undefined4*)((char*)this + 4);
        // Update next pointer at node+8 to point to itself? (self-loop)
        *(int*)(*(int*)((char*)this + 4) + 8) = *(int*)((char*)this + 4);
        // Re-read head pointer
        headNodePtr = *(int**)((char*)this + 4);
        // Output: {this, headNodePtr}
        outPair[0] = (int)this;
        outPair[1] = (int)headNodePtr;
        return;
    }

    while (true) {
        if (list1 == 0 || list1 != node2) { // note: uses node2 as list check? This might be misleading
            FUN_00b97aea();
        }
        if (node1 == node2) break;
        FUN_008ea1d0();               // advance/next operation
        FUN_008ed9d0(local, list1, node1); // copy or transform node
    }
    outPair[0] = (int)list1;
    outPair[1] = (int)node1;
    return;
}