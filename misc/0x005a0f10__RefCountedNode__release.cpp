// FUNC_NAME: RefCountedNode::release
void RefCountedNode::release() {
    // Check if the list is non-empty (next pointer doesn't point to the node's own prev)
    // If so, cleanup the list (unlink and delete all nodes)
    if (field_0x08 != reinterpret_cast<uintptr_t>(&field_0x0C)) {
        cleanupList(field_0x08); // removes nodes from this head
    }

    // Release two reference-counted objects at +0x10 and +0x0C
    int* ptrArray = reinterpret_cast<int*>(this + 0x14); // points to +0x14
    for (int i = 1; i >= 0; --i) {
        int* objectPtr = reinterpret_cast<int*>(*ptrArray--); // load pointer at current offset minus 4
        if (objectPtr != nullptr) {
            if (--(*objectPtr) == 0) { // decrement ref count
                if (*ptrArray != 0) { // verify pointer is still valid
                    deallocationPrep();
                    (*deallocFunc)(*ptrArray, 0x30); // custom free with size 0x30
                }
            }
        }
    }
}