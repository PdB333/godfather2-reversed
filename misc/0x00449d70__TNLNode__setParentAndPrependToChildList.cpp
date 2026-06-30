// FUNC_NAME: TNLNode::setParentAndPrependToChildList
// Address: 0x00449d70
// Sets the parent node and inserts this node as the first child of that parent.
// Offsets: +0x00 = m_parent (pointer to parent node), +0x04 = m_nextSibling (pointer to next sibling in parent's child list)

void __thiscall TNLNode::setParentAndPrependToChildList(int* pThis, int newParent)
{
    if (pThis[0] != newParent) {
        // Remove from old parent's child list (if any)
        if (pThis[0] != 0) {
            removeFromCurrentParent(pThis);
        }
        // Assign new parent
        pThis[0] = newParent;
        // If new parent exists, prepend this node to its child list
        if (newParent != 0) {
            pThis[1] = *(int*)(newParent + 4);                // this->next = parent->firstChild
            *(int**)(newParent + 4) = pThis;                 // parent->firstChild = this
        }
    }
}