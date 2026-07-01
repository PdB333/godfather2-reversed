// FUNC_NAME: ObjectList::setHeadObject
void __thiscall ObjectList::setHeadObject(void* this, void* object)
// Sets the head of an intrusive doubly-linked list.
// The list head pointer is at this+0xe8. The list nodes are embedded at object+0x48.
// Each node has a 'next' pointer at +0 and a 'prev' pointer at +4 (which points to the address of the pointer that points to this node, not to the previous node).
{
    // Check if we are trying to set head to null and the object's flag at +0x50 (bit0 = 1 means allowed, 0 means not)
    if ((object == 0) && ((*(uint8_t*)((uint32_t)this + 0x50) & 1) == 0))
    {
        // Initialize/reset something (likely a temporary state)
        maybeInitialize();
    }

    // Pointer to the head pointer variable
    int** headPointerPtr = (int**)((uint32_t)this + 0xe8);
    // Compute the address of the node inside the object
    int* newNode = object ? (int*)((uint32_t)object + 0x48) : 0;

    if (*headPointerPtr != newNode)
    {
        // Remove the old head if present
        if (*headPointerPtr != 0)
        {
            detachNode(headPointerPtr);
        }
        // Set new head
        *headPointerPtr = newNode;
        if (newNode != 0)
        {
            // Store the previous prev pointer of the new node (which points to its old list)
            *(int**)((uint32_t)this + 0xec) = (int*)*(newNode + 1); // newNode[1] is the prev pointer
            // Set the new node's prev to point to the head pointer variable itself
            *(int**)((uint32_t)newNode + 4) = headPointerPtr;
        }
    }
}