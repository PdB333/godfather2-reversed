// FUNC_NAME: IntrusiveNode::insertAfter
int * __thiscall IntrusiveNode::insertAfter(int *this, int parentObj)
{
    // If parentObj is non-null, it points to an object with an embedded node at offset +0x48.
    if (parentObj != 0) {
        parentObj = parentObj + 0x48;
    }

    // Only relink if the new previous node is different from the current one.
    if (this[0] != parentObj) { // this->prev
        // Remove this node from its current list if it is already linked.
        if (this[0] != 0) {
            FUN_004daf90(this); // IntrusiveNode::remove(this)
        }

        // Set the prev pointer to the new node (or null).
        this[0] = parentObj; // this->prev = newPrev

        if (parentObj != 0) {
            // Insert this node after the new previous node.
            this[1] = *(int *)(parentObj + 4); // this->next = newPrev->next
            *(int **)(parentObj + 4) = this;   // newPrev->next = this
        }
    }

    return this;
}