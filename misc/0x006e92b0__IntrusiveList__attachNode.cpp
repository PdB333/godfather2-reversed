// FUNC_NAME: IntrusiveList::attachNode
void __thiscall IntrusiveList::attachNode(int thisPtr, int containerObj)
{
    // thisPtr is the list head object
    // Structure offsets:
    // +0x98: pointer to first node (or null)
    // +0x9c: temporary storage for old list head pointer (used in node hook)
    // +0xa8: reference count (byte, decremented each call)

    // containerObj is a larger object containing an IntrusiveNode at offset 0x48
    // IntrusiveNode has a hook at offset 0x4 (pointer-to-pointer to list head)
    // The hook is used for O(1) removal

    // Get pointer to the node within containerObj
    int nodePtr;
    if (containerObj == 0) {
        nodePtr = 0;
    } else {
        nodePtr = containerObj + 0x48;
    }

    // Pointer to the list head field in this object
    int* headField = (int*)(thisPtr + 0x98);

    if (*headField != nodePtr) {
        // Remove old node from list if present (unlink)
        if (*headField != 0) {
            FUN_004daf90(headField);
        }
        // Set new head
        *headField = nodePtr;

        if (nodePtr != 0) {
            // Update the node's hook: store old head pointer into node+4
            *(int *)(thisPtr + 0x9c) = *(int *)(nodePtr + 4);
            // Then point node's hook to the list head field
            *(int **)(nodePtr + 4) = headField;
        }
    }

    // Decrement reference count
    *(char *)(thisPtr + 0xa8) = *(char *)(thisPtr + 0xa8) - 1;
    return;
}