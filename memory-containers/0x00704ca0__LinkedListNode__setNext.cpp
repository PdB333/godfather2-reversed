// FUNC_NAME: LinkedListNode::setNext
// Address: 0x00704ca0
// This function sets the 'next' pointer of an intrusive doubly-linked list node.
// The node structure is embedded in containing objects at offset 0x48.
// 'this' points to a node's next pointer field (offset +4 from container), and param_2 is a pointer to another container.
// Offsets: this+4 = next pointer (points to the next node's container+0x48)
//          this+8 = prev link (pointer to the previous node's 'next' field)
//          param_2+0x48 = the target node (container's embedded node)
//          param_2+0x4c = the target node's prev link field

void __thiscall LinkedListNode::setNext(ContainerObject* otherContainer) {
    int** nextField = (int**)(this + 4); // Pointer to the next pointer (this node's next)
    if (otherContainer == 0) {
        // Clear: if next points to non-null and not a special sentinel value (0x48), release it
        if (*nextField != 0 && *nextField != 0x48 && *nextField != 0) {
            FUN_004daf90(nextField);   // Release the node pointed to by next
            *nextField = 0;
        }
    } else {
        int* newNext = (int*)((int)otherContainer + 0x48); // Address of the other container's embedded node
        if (*nextField != newNext) {
            if (*nextField != 0) {
                FUN_004daf90(nextField);   // Release old next node
            }
            *nextField = newNext;
            if (newNext != 0) {
                // Save the old prevLink of the target node into this node's prevLink field
                *(int*)(this + 8) = *(int*)((int)otherContainer + 0x4c);
                // Set the target node's prevLink to point to this node's nextField
                *(int**)((int)otherContainer + 0x4c) = nextField;
            }
        }
    }
}