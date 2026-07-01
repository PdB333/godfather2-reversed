// FUNC_NAME: Entity::setParent
// Function at 0x007e0b10 - Sets the parent object for an entity, managing an intrusive linked list of children.
// The entity stores a pointer to its parent's child link node at +0x104 (m_pParentLinkNode).
// The parent object has an embedded link node at offset +0x48 used to chain children.
// The field at +0x108 (m_pParentLinkNext) is used during insertion to update the list.

void __thiscall Entity::setParent(Entity* this, Entity* newParentOrNull)
{
    // Pointer to the entity's field that stores the current parent link node address
    int* pParentLinkNode = (int*)((int)this + 0x104);  // +0x104: m_pParentLinkNode

    // Compute the new parent link node: if newParent is non-null, it's at offset 0x48 within the parent
    int newParentLinkNode = (newParentOrNull != 0) ? ((int)newParentOrNull + 0x48) : 0;  // +0x48: parent's child link node

    // Only update if the parent actually changes
    if (*pParentLinkNode != newParentLinkNode)
    {
        // If there was an old parent, detach from its list
        if (*pParentLinkNode != 0)
        {
            // FUN_004daf90 removes the link node (pointed to by pParentLinkNode) from its containing list
            removeFromParentList(pParentLinkNode);  // defined at 0x004daf90
        }

        // Set the new parent link node
        *pParentLinkNode = newParentLinkNode;

        // If the new parent is valid, insert this entity into the parent's child list
        if (newParentLinkNode != 0)
        {
            // Update this entity's "next" field (+0x108) with the old next from the parent's link node
            *(int*)((int)this + 0x108) = *(int*)(newParentLinkNode + 4);  // +0x108: m_pParentLinkNext

            // Make the parent's link node's next point back to this entity's m_pParentLinkNode field
            *(int**)(newParentLinkNode + 4) = pParentLinkNode;  // parent's link node + 4: m_pNext
        }
    }
}