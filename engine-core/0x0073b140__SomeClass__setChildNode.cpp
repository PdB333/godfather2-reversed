// FUNC_NAME: SomeClass::setChildNode
void __thiscall SomeClass::setChildNode(int* newChildOwner) {
    int** childLinkPtr = (int**)(this + 0x70); // +0x70: pointer to child node link (a pointer to the actual child node)
    int* newChildNode;

    if (newChildOwner == 0) {
        newChildNode = 0;
    } else {
        // The child node structure is at offset 0x48 within the owner object
        newChildNode = (int*)(newChildOwner + 0x48);
    }

    if (*childLinkPtr != newChildNode) {
        // If there was an existing child, detach it (destroy or remove)
        if (*childLinkPtr != 0) {
            FUN_004daf90(childLinkPtr); // detachChild(childLinkPtr)
        }
        *childLinkPtr = newChildNode;

        if (newChildNode != 0) {
            // Save the old back-pointer (pointer to the previous child link) into this->m_prevChildLink (+0x74)
            *(int**)(this + 0x74) = *(int**)(newChildNode + 4);
            // Set the child's back-pointer to point to our child link field
            *(int**)(newChildNode + 4) = childLinkPtr;
        }
    }
}