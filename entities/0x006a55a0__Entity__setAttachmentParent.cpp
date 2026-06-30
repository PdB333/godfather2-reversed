// FUNC_NAME: Entity::setAttachmentParent
// Function at 0x006a55a0
// Sets a linked parent pointer and resets local transform to zero.
void __thiscall Entity::setAttachmentParent(int* parentLink)
{
    // Pointer to the head of the child list (this + 0x694)
    int** listHead = reinterpret_cast<int**>(this + 0x694);
    if (listHead != parentLink) // Ensure we aren't linking to ourselves
    {
        int newHead = *parentLink;         // Value from parent link field
        int oldHead = *listHead;           // Current head of child list
        if (oldHead != newHead)
        {
            if (oldHead != 0)
            {
                // Remove previous head from list (likely unlinks the node)
                unlinkNodeFromList(listHead); // FUN_004daf90
            }
            *listHead = newHead; // Set new head
            if (newHead != 0)
            {
                // Preserve the node's old back pointer and update it to point to listHead
                // this + 0x698 stores the previous back pointer (possible tail)
                *reinterpret_cast<int*>(this + 0x698) = *reinterpret_cast<int*>(newHead + 4);
                *reinterpret_cast<int**>(newHead + 4) = listHead;
            }
        }
    }
    // Reset local position/transform to zero (offset 0x14, 0x18, 0x1c)
    *reinterpret_cast<Vector3*>(this + 0x14) = Vector3(0.0f, 0.0f, 0.0f);
}