// FUNC_NAME: rebuildSortedIndices

// This function rebuilds two parallel sorted arrays from a linked list of data arrays.
// It frees previous arrays, allocates new ones (two halves), copies non-zero elements,
// then sorts each half independently.

// Unknown class layout (offsets from this):
// +0x00: vtable pointer
// +0x04: pointer to first array (m_pArrayFirst)
// +0x08: pointer to second array (m_pArraySecond)
// +0x0C: count of elements (m_count)
// +0x10: byte flag (m_flag)
// +0x14: pointer to head of linked list (m_pNodeList)
// Node layout:
// +0x00: pointer to data (int*)
// +0x04: number of elements (int)
// +0x08: pad/unknown (4 bytes)
// +0x0C: next node pointer (Node*)

void SomeClass::rebuildSortedIndices() {
    // If previously allocated, free the arrays using vtable[4] (deallocate)
    if (m_pArrayFirst != nullptr) {
        (this->vtable->deallocate)(m_pArrayFirst, 0);
    }

    // Temporary allocator context (12 bytes)
    int allocContext[3] = {0, 0, 0};

    // Use vtable[0] (allocate) to get memory for two arrays (each m_count elements)
    int* pArrayFirst = (int*)(this->vtable->allocate)(m_count * 8, &allocContext);
    int* pArraySecond = pArrayFirst + m_count; // pointer to second half

    m_pArrayFirst = pArrayFirst;
    m_pArraySecond = pArraySecond;

    // Walk through linked list and copy non-zero entries into both arrays
    Node* node = m_pNodeList; // head
    while (node != nullptr) {
        int* data = node->data;
        int count = node->count;
        for (int i = 0; i < count; ++i) {
            int value = *data++;
            if (value != 0) {
                *pArrayFirst++ = value;
                *pArraySecond++ = value;
            }
        }
        node = node->next; // +0x0C
    }

    // Update count to number of actual elements copied
    m_count = pArrayFirst - m_pArrayFirst;

    // Sort each array (functions 0x00588160 and 0x00588250)
    // The last argument is a magic number derived from EBP (flags/seed)
    int sortFlags = (0x005878e0 >> 8) << 8; // placeholder; actual would come from caller context
    sortFirstArray(m_pArrayFirst, pArrayFirst, m_count, sortFlags);
    sortSecondArray(m_pArraySecond, pArraySecond, m_count, sortFlags);

    // Clear flag at offset 0x10
    m_flag = 0;
}