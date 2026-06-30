// FUNC_NAME: Node::setLinkedPointer
void __thiscall Node::setLinkedPointer(int newPointer) {
    int currentPointer;
    int *thisPtr = reinterpret_cast<int*>(this);
    
    // Compute the pointer to the header block (if newPointer is non-zero, offset 0x4c)
    int *newHeader = newPointer ? reinterpret_cast<int*>(newPointer + 0x4c) : nullptr;
    
    // If the current pointer at offset 0 differs from the new one
    if (thisPtr[0] != reinterpret_cast<int>(newHeader)) {
        // Remove this node from the old list if it was linked
        if (thisPtr[0] != 0) {
            FUN_004daf90(this); // remove from current list
        }
        
        // Store the new pointer (offset 0)
        thisPtr[0] = reinterpret_cast<int>(newHeader);
        
        // If new header is non-null, insert this node at the head of its linked list
        if (newHeader != nullptr) {
            // Set this node's next pointer (offset 4) to the current head of the list
            thisPtr[1] = newHeader[1];
            // Update the list head to point to this node
            newHeader[1] = reinterpret_cast<int>(thisPtr);
        }
    }
}