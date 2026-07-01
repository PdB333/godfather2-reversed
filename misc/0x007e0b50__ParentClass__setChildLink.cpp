// FUNC_NAME: ParentClass::setChildLink
// Address: 0x007e0b50
// This function attaches a child object to this parent using an intrusive doubly-linked list node embedded in the child at offset 0x48.
// The parent stores a pointer to the child's link node (0x10c) and a copy of the child's previous pointer (0x110).
// The child's link node's prev pointer is set to point to the parent's pointer location, enabling O(1) detachment.

void __thiscall ParentClass::setChildLink(void* thisPtr, void* childObj) {
    // Pointer to the parent's link field (holds address of child's link node)
    int** childLinkPtr = (int**)((int)thisPtr + 0x10c);
    int* newLinkField; // Address of child's link node (offset 0x48)

    if (childObj == nullptr) {
        newLinkField = nullptr;
    } else {
        newLinkField = (int*)((int)childObj + 0x48);
    }

    // Only update if the new link differs from the current one
    if (*childLinkPtr != newLinkField) {
        // Remove existing child if present
        if (*childLinkPtr != nullptr) {
            detachChild(childLinkPtr); // FUN_004daf90 - likely removes the child from the list
        }

        // Store new child's link node address
        *childLinkPtr = newLinkField;

        if (newLinkField != nullptr) {
            // Save the child's previous pointer (offset 4 of link node) into parent field 0x110
            *(int*)((int)thisPtr + 0x110) = *(int*)(newLinkField + 1); // newLinkField[1] = prev pointer

            // Set child's prev pointer to point to the parent's pointer location
            *(int**)newLinkField[1] = childLinkPtr; // Same as *(int**)(newLinkField + 4) = childLinkPtr
        }
    }
    return;
}