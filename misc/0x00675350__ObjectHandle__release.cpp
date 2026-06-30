// FUNC_NAME: ObjectHandle::release

// 0x00675350
// Releases an object handle by removing its associated node and itself from the owning array.
// The handle structure layout (pointed to by this):
//   +0x00: m_pArray (pointer to the array container)
//   +0x04: unused (padding?)
//   +0x08: unused
//   +0x0C: unused
//   +0x10: m_pNode (pointer to a node structure)
// The array container layout (at m_pArray):
//   +0x00: (unknown)
//   +0x04: m_nCount (number of active entries)
//   +0x08: (unknown)
//   +0x0C: m_ppEntries (array of pointers to items)
// Node structure (at m_pNode - 0x10):
//   +0x00: (node data, 16 bytes)
//   +0x08: m_nIndex (index in m_ppEntries, stored as int at offset -8 from m_pNode)
// The handle object itself has a header at (this - 4) containing the index for itself (this[-2]).
void __thiscall ObjectHandle::release(void)
{
    int* pArray;
    int* pNode;
    int nCount;

    if (this == nullptr)
        return;

    // ---- Release the node pointer (offset +0x10) ----
    pNode = (int*)this[4];           // m_pNode
    pArray = (int*)this[0];          // m_pArray

    if (pNode != nullptr)
    {
        // Clear the slot in the array: m_ppEntries[ node->m_nIndex ] = nullptr
        *(int*)(*(pArray + 3) + pNode[-2] * 4) = 0; // pArray+3 = &m_ppEntries

        // Decrease the count
        pArray[1] = pArray[1] - 1;   // m_nCount

        // Free the node structure (starts 0x10 bytes before pNode)
        (*g_freeFunc)((char*)pNode - 0x10);
    }

    // ---- Release the handle itself ----
    pArray = (int*)this[0];          // reload m_pArray

    // Clear the slot for this handle: m_ppEntries[ this[-2] ] = nullptr
    *(int*)(*(pArray + 3) + this[-2] * 4) = 0; // this[-2] is index stored in header

    // Decrease the count
    pArray[1] = pArray[1] - 1;       // m_nCount

    // Free the handle structure (starts 4 bytes before this)
    (*g_freeFunc)((char*)this - 4);
}