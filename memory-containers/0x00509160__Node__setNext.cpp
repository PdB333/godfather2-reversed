//FUNC_NAME: Node::setNext
// Function at 0x00509160: Sets the next pointer of this node to the node embedded at offset 0x48 in param_2.
// Handles doubly linked list insertion/removal.
void __thiscall Node::setNext(Node* this, void* param_2) {
    // this+0x14: pointer to next node (or null)
    int** nextPtr = (int**)((char*)this + 0x14);
    // If param_2 is non-null, treat it as an object with an embedded node at offset 0x48
    int* newNext = (param_2 != 0) ? (int*)((char*)param_2 + 0x48) : 0;
    
    if (*nextPtr != newNext) {
        // Remove old next node from list if it exists
        if (*nextPtr != 0) {
            FUN_004daf90(nextPtr); // unlink function
        }
        // Set new next pointer
        *nextPtr = newNext;
        if (newNext != 0) {
            // Update this node's prev pointer (offset 0x18) to the new node's old prev
            *(int*)((char*)this + 0x18) = *(int*)((char*)newNext + 4);
            // Set new node's prev pointer to point to this node's next pointer location
            *(int**)((char*)newNext + 4) = nextPtr;
        }
    }
}