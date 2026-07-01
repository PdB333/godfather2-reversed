//FUNC_NAME: Pool::push
void __thiscall Pool::push(int thisPtr, int itemPtr)
{
    int node;
    int savedNext;

    // Check if container is not full (size at +0x1c < capacity at +0x14)
    if (*(int *)(thisPtr + 0x1c) < *(int *)(thisPtr + 0x14))
    {
        // If item is null, node is null; otherwise node points to item's next pointer field at +0x48
        if (itemPtr == 0)
        {
            node = 0;
        }
        else
        {
            node = itemPtr + 0x48;
        }

        savedNext = 0;
        if (node != 0)
        {
            // Save the current next pointer (at node+4) and then set it to point to the stack node (circular/list insertion)
            savedNext = *(int *)(node + 4);
            *(int **)(node + 4) = &node;
        }

        // Call internal push/insert function with the node
        FUN_0094ec40(&node);

        // Update global state (likely a manager or allocator)
        FUN_00408680(&DAT_012069c4);

        // If node was non-null, call cleanup/destructor
        if (node != 0)
        {
            FUN_004daf90(&node);
        }
    }
}