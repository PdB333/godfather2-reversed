// FUN_NAME: ContainerList::clearAll
// Address: 0x004bc7d0
// Clears all objects in the list, calls destructor on each, zeros the storage array.

// This implements a free-list-based pool with an internal array.
// The allocated objects are tracked via a singly linked list of nodes.
// Each node holds a pointer to its slot in the storage array.
// The slot itself stores the address of the next node.

// Class structure (assumed):
// +0x00: PoolHeader* m_pHeader
// +0x04: int m_nFreeCount        // set to 0 after clearing
// +0x08: int m_nCapacity         // size of the slot array (inclusive upper bound)
// +0x0C: int field_0C            // unused here
// +0x10: int m_nActiveCount      // decremented as each item is destroyed

// PoolHeader structure:
// +0x00: int field_00
// +0x04: int field_04
// +0x08: int* m_pArray           // pointer to the slot array

// Node structure:
// +0x00: int field_00
// +0x04: int field_04
// +0x08: int* m_pSlot           // pointer to this node's slot in the array

// The slot array element contains the address of the next node (int*).

void ContainerList::clearAll()
{
    // Field at +0x00: m_pHeader
    PoolHeader* pHeader = m_pHeader;

    // +0x08 from header: m_pArray
    int* pArray = pHeader->m_pArray;

    // First node address is stored at array[0] (double dereference)
    int* pCurrent = (int*)*pArray;

    while (pCurrent != 0)
    {
        // Node+0x08: m_pSlot (pointer to its slot element)
        // Slot element contains the address of the next node
        int* pNext = (int*)*pCurrent->m_pSlot;

        // Call destructor or finalizer on the slot data
        FUN_009c8f10(pCurrent->m_pSlot);   // destroys the item stored in the slot

        // Free the node itself
        FUN_009c8eb0(pCurrent);             // returns node to the free list

        // Decrement active item counter (+0x10 in the container)
        m_nActiveCount--;

        pCurrent = pNext;
    }

    // Zero out the entire storage array
    for (int i = 0; i <= m_nCapacity; i++)
    {
        pArray[i] = 0;
    }

    // Reset the free count (offset +0x04)
    m_nFreeCount = 0;
}