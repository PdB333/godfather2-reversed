// FUNC_NAME: Entity::destroyRecursive
void __fastcall Entity::destroyRecursive(Entity* this)
{
    int node;

    // Set flag indicating this entity is being destroyed (0x200000 bit in flags at +0xc)
    *(uint*)((int)this + 0xc) |= 0x200000;

    // Notify system of destruction (e.g., remove from spatial hash, detach from parent)
    FUN_0051d6b0(); // likely Entity::onDestroy()

    // Remove self from linked list if present
    // +0x8 holds address of the pointer that points to this entity (i.e., &(parent->child) or global head)
    if (*(int**)((int)this + 0x8) != (int*)0)
    {
        // Clear the pointer that points to this entity (unlink)
        **(int**)((int)this + 0x8) = 0;
        // Clear the stored reference to the linking pointer
        *(int*)((int)this + 0x8) = 0;
    }

    // Iterate over the global list of all entities (head at DAT_01205514)
    node = DAT_01205514; // g_entityListHead
    while (node != 0)
    {
        // Check if node is a child: parent pointer (+0x18) equals this
        // AND child has not yet been flagged for destruction
        if ( (*(int*)(node + 0x18) == (int)this) && ((*(uint*)(node + 0xc) & 0x200000) == 0) )
        {
            // Recursively destroy the child
            Entity::destroyRecursive((Entity*)node);
        }
        // Move to next node in global list (next link at +0x14)
        node = *(int*)(node + 0x14);
    }

    return;
}