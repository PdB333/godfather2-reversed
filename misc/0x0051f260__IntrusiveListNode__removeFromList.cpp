// FUNC_NAME: IntrusiveListNode::removeFromList

void __thiscall IntrusiveListNode::removeFromList() {
    // This object contains embedded list pointers at offsets +0x124 (next) and +0x128 (prev).
    // The list is a circular doubly linked list where the head (sentinel) is stored elsewhere.
    
    int* nextField = reinterpret_cast<int*>(this) + 0x49; // &(this->next)
    int* nextNodePtr = reinterpret_cast<int*>(*nextField); // this->next (pointer to next node)
    
    if (nextNodePtr != nullptr) {
        // nextNode->prev is at offset 4 in the node (assuming node layout: [next, prev])
        int* nextNodePrev = reinterpret_cast<int*>(nextNodePtr[1]); 
        
        if (nextNodePrev == nextField) {
            // This node is the first in the list; bypass it by updating the next node's prev pointer.
            nextNodePtr[1] = reinterpret_cast<int>(reinterpret_cast<int*>(this)[0x4a]); // next->prev = this->prev
            // Mark object as destroyed by setting vtable to a sentinel
            *reinterpret_cast<int**>(this) = &PTR_LAB_00e38340;
            return;
        }
        
        // General case: find the predecessor node (whose next points to this->next)
        int* predecessor = nextNodePrev;
        while (reinterpret_cast<int*>(predecessor[1]) != nextField) {
            predecessor = reinterpret_cast<int*>(predecessor[1]);
        }
        // Remove this node by linking predecessor->next = this->prev
        predecessor[1] = reinterpret_cast<int>(reinterpret_cast<int*>(this)[0x4a]);
    }
    
    // Unlink complete; replace vtable with a dead sentinel
    *reinterpret_cast<int**>(this) = &PTR_LAB_00e38340;
}