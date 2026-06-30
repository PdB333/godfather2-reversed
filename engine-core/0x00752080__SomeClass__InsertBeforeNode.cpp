// FUNC_NAME: SomeClass::InsertBeforeNode
void __thiscall SomeClass::InsertBeforeNode(int this, int param2) // param2 is target object pointer
{
    // The class has an embedded linked list node at offset 0x58 (next) and 0x5c (prev).
    // The target object has a linked list node at offset 0x48 (next) and 0x4c (prev).
    int *nextField = (int *)(this + 0x58); // address of this->listNode.next

    int targetNodePtr = param2;
    if (param2 == 0) {
        targetNodePtr = 0;
    } else {
        targetNodePtr = param2 + 0x48; // address of target's listNode (the node's base)
    }

    if (*nextField != targetNodePtr) {
        // If this node is already linked, remove it from the old list
        if (*nextField != 0) {
            FUN_004daf90(nextField); // remove this node from its current list
        }

        // Set this node's next to point to the target node's list header
        *nextField = targetNodePtr;

        if (targetNodePtr != 0) {
            // Update this node's prev: copy the target's prev into this->prev
            *(int *)(this + 0x5c) = *(int *)(targetNodePtr + 4);
            // Make the target's prev point back to this node's next field
            *(int **)(targetNodePtr + 4) = nextField;
        }
    }
}