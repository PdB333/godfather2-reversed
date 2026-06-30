// FUNC_NAME: ObjectPool::clear
void __thiscall ObjectPool::clear() {
    // ESI = this (ObjectPool*)
    // ObjectPool layout:
    // +0x00: InternalPool* m_pInternal   // pointer to pool control block
    // +0x04: int          m_freeIndex    // reset to 0
    // +0x08: int          m_arraySize    // number of elements in the node array
    // +0x10: int          m_nodeCount    // decremented per node freed

    // InternalPool layout (pointed to by m_pInternal):
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: int*         m_pHeadNode;   // pointer to the first node (also base of node array)

    InternalPool* internal = *reinterpret_cast<InternalPool**>(this); // offset 0x00
    int** headSlot = reinterpret_cast<int**>(reinterpret_cast<char*>(internal) + 8); // address of m_pHeadNode
    int* current = *headSlot; // first real node (m_pHeadNode points to a sentinel? Actually double deref)

    while (current != nullptr) {
        // Node layout: offset 0x00: ? (data), offset 0x08: next pointer
        int* next = *reinterpret_cast<int**>(current + 2); // current[2] = next pointer (offset 0x08)

        // Free the data pointed to by the next node? (passes the next pointer itself)
        releaseNodeData(reinterpret_cast<int*>(current[2])); // FUN_009c8f10
        // Delete the current node structure
        deleteNode(current); // FUN_009c8eb0

        // Decrement the active node count
        reinterpret_cast<int*>(this)[4] += -1; // offset 0x10

        current = next;
    }

    // Clear the entire node array (treated as int array starting at the same address as m_pHeadNode)
    int* arrayBase = *headSlot; // same as the head node pointer address
    int bound = reinterpret_cast<int*>(this)[2]; // offset 0x08 = m_arraySize
    for (int i = 0; i <= bound; ++i) {
        arrayBase[i] = 0;
    }

    // Reset the free index
    reinterpret_cast<int*>(this)[1] = 0; // offset 0x04 = m_freeIndex
}