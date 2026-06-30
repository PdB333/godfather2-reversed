// FUNC_NAME: Node::RemoveFromListAndCleanup
void Node::RemoveFromListAndCleanup(void)
{
    // Remove this node from its doubly linked list if it is currently inserted.
    // Offset +0x14: flag indicating whether the node is in the list (non-zero means present).
    if (*(int*)((int)this + 0x14) != 0)
    {
        *(undefined4*)((int)this + 0x14) = 0;

        // Adjust the list pointers.
        // Offset +0x0c = prev pointer, +0x10 = next pointer.
        if (*(int*)((int)this + 0x0c) == 0)
        {
            // If this node is the head, update the global list head.
            DAT_01205a28 = *(undefined4*)((int)this + 0x10);
        }
        else
        {
            // Set previous node's next to this node's next.
            *(undefined4*)(*(int*)((int)this + 0x0c) + 0x10) = *(undefined4*)((int)this + 0x10);
        }

        if (*(int*)((int)this + 0x10) != 0)
        {
            // Set next node's prev to this node's prev.
            *(undefined4*)(*(int*)((int)this + 0x10) + 0x0c) = *(undefined4*)((int)this + 0x0c);
        }

        // Clear the node's own links.
        *(undefined4*)((int)this + 0x0c) = 0;
        *(undefined4*)((int)this + 0x10) = 0;
    }

    // Iterate over a child list starting at offset +0x1c.
    // The child list is singly linked using offset +0x0c as the "next" pointer.
    for (int* child = *(int**)((int)this + 0x1c); child != (int*)0; child = *(int**)((int)child + 0x0c))
    {
        // Offset +0x04: a flag that, when set, requires cleanup.
        if (*(int*)(child + 1) != 0) // +0x04 relative to child
        {
            *(undefined4*)((int)child + 4) = 0;
            CleanupChild(); // FUN_0064d500
        }
    }
}