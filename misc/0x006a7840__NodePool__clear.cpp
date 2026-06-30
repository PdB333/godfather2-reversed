// FUNC_NAME: NodePool::clear
void __thiscall NodePool::clear(int* this) {
    // Offset 0: pointer to vtable (or base struct)
    // Offset 8 from base: pointer to linked list head (or free list)
    // Offset 16 (param_1[4]): count
    // Offset 8 (param_1[2]): capacity/size

    int* base = *(int**)this;  // read vtable pointer? Actually *this is first member
    int node = *(int*)(base + 2);  // head of list (offset 8 from base)
    while (node != 0) {
        int nextNode = *(int*)(node + 2);  // next pointer at offset 8 in node
        // Release the data stored at offset 8 of the node (reinterpreted)
        releaseData((void*)*(int*)(node + 2));
        // Destroy the node itself
        destroyNode((void*)node);
        this[4]--;  // decrement count
        node = nextNode;
    }
    // Clear the free slot array (base + 8 is actually an array of pointers)
    int* ptrArray = *(int**)(base + 2);
    for (unsigned int i = 0; i <= (unsigned int)this[2]; i++) {
        ptrArray[i] = 0;
    }
    this[1] = 0;  // reset count? or first free index
}