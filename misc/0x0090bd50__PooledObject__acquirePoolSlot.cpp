// FUNC_NAME: PooledObject::acquirePoolSlot
int __thiscall PooledObject::acquirePoolSlot(void)
{
    // this pointer in param_1 (implicit)
    int* slotPtr = (int*)((char*)this + 0x14); // +0x14: m_slotNode pointer
    int newSlotNode;

    // Check if current slot is null or sentinel value 0x48
    if (*slotPtr == 0 || *slotPtr == 0x48)
    {
        // Try to get a free slot from the global pool manager
        int** poolHead = (int**)(DAT_012233a0 + 4); // global pool manager (DAT_012233a0) holds a pointer to a free list head at +4
        if (**poolHead == 0)
        {
            newSlotNode = 0;
        }
        else
        {
            // dereference to get the first free node's address, then adjust by -0x1f30 (likely offset to owning object)
            newSlotNode = **poolHead - 0x1f30;
        }
        if (newSlotNode == 0)
        {
            newSlotNode = 0;
        }
        else
        {
            // Add 0x48 to get the actual slot node address (slot size = 0x48)
            newSlotNode += 0x48;
        }

        // Update slot if different from current
        if (*slotPtr != newSlotNode)
        {
            // Remove old slot node if present
            if (*slotPtr != 0)
            {
                unlinkSlotNode(slotPtr); // FUN_004daf90: removes the handle from the linked list
            }
            *slotPtr = newSlotNode;
            // Insert new slot node into the list (list head at newSlotNode+4)
            if (newSlotNode != 0)
            {
                *(int*)((char*)this + 0x18) = *(int*)(newSlotNode + 4); // +0x18: m_prevSlotNode
                *(int**)(newSlotNode + 4) = slotPtr; // update list head to point to this object's slot pointer
            }
        }
    }

    // Return the owning object (slot node address - 0x48)
    if (*slotPtr == 0)
    {
        return 0;
    }
    return *slotPtr - 0x48;
}