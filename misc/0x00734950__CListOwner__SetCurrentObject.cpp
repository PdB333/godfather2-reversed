// FUNC_NAME: CListOwner::SetCurrentObject
// Address: 0x00734950
// Role: Sets the current object managed by this list owner. The object is expected to have an intrusive node at offset 0x48.
// The old current object is released (if any) and replaced with the new one. The list node is updated to point back to the owner.
// Also fires virtual callbacks before and after the change.

// Assuming the offset to the intrusive node inside each managed object is 0x48 (72 bytes).
// The class has two fields at offsets:
// +0x1D3 (0x74C bytes): pointer to the current node (list head)
// +0x1D4 (0x750 bytes): temporary storage for the node's old 'prev' link (used for re-linking)

// The intrusive node structure (embedded at +0x48 in objects):
// +0x00: next pointer (int)
// +0x04: prev pointer (int) - this is a pointer to the head pointer of the owner, effectively a "backlink" to the owner's list head.

void __thiscall CListOwner::SetCurrentObject(int param_1, int pNewObject) {
    int *ppHead = (int *)(param_1 + 0x1D3); // pointer to the "current node" field
    int *pOldObject = (*ppHead != 0) ? (*ppHead - 0x48) : 0; // convert current node pointer to containing object

    if (pNewObject != pOldObject) {
        // Call virtual function at vtable+0x260 (e.g., OnCurrentChanging)
        (*(void (**)(void))(*param_1 + 0x260))();

        // Convert new object pointer to its embedded node pointer
        int pNewNode = (pNewObject != 0) ? (pNewObject + 0x48) : 0;

        if (*ppHead != pNewNode) {
            // Release the old node if it existed
            if (*ppHead != 0) {
                FUN_004daf90(ppHead); // Unlink and possibly free the node
            }
            *ppHead = pNewNode; // Set new head node

            if (pNewNode != 0) {
                // Save the old prev link of the new node into the owner's second field
                param_1[0x1D4] = *(int *)(pNewNode + 4);
                // Make the new node's prev point back to the owner's head pointer field
                *(int **)(pNewNode + 4) = ppHead;
            }
        }
    }

    // If a node is now active (non-zero and not the sentinel value 0x48), call a post-change callback
    if (*ppHead != 0 && *ppHead != 0x48) {
        // Call virtual function at vtable+0x25c (e.g., OnCurrentChanged)
        (*(void (**)(void))(*param_1 + 0x25c))();
    }
    return;
}