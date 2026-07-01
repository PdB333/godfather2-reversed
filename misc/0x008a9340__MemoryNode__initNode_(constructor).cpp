// FUNC_NAME: MemoryNode::initNode (constructor)
// This function initializes a memory node in a custom allocator's free list.
// It sets the vtable pointer, updates neighboring node links, calls a base initializer,
// and optionally frees the object if the allocation failed (param_2 & 1).
// Offsets:
//   +0x18: m_pPrev (pointer to previous node)
//   +0x1c: m_pNext (pointer to next node)
//   +0x20: m_pData (pointer to associated data block)
//   +0x28: vtable pointer

int __thiscall MemoryNode::initNode(int thisPtr, byte param_2)
{
    // Set vtable pointer to global vtable table
    *(void ***)(thisPtr + 0x28) = &PTR_LAB_00e317cc;

    // If this node has a previous neighbor
    if (*(int *)(thisPtr + 0x18) != 0) {
        // Update link to skip this node (removing it from list)
        if (*(int *)(thisPtr + 0x1c) == 0) {
            // No next node: point previous node's forward link to data block
            *(int *)(*(int *)(thisPtr + 0x18) + 4) = *(int *)(thisPtr + 0x20);
        } else {
            // Point next node's backward link to data block
            *(int *)(*(int *)(thisPtr + 0x1c) + 8) = *(int *)(thisPtr + 0x20);
        }
        // Update data block's backward link (if it exists)
        if (*(int *)(thisPtr + 0x20) != 0) {
            *(int *)(*(int *)(thisPtr + 0x20) + 4) = *(int *)(thisPtr + 0x1c);
        }
    }

    // Call some base class initializer (e.g., allocate or zero memory)
    FUN_0064d150();

    // If the allocation flag is set, free this node
    if ((param_2 & 1) != 0) {
        FUN_009c8eb0(thisPtr); // operator delete
    }
    return thisPtr;
}