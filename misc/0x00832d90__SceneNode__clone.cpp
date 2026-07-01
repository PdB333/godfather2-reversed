// FUNC_NAME: SceneNode::clone
bool SceneNode::clone(int *pSourceData, int *pParentNode)
{
    bool bFromPool = true;
    char isValid;
    int *pNewNode;
    void **pMemoryManager;
    int *pParentData;

    // Check if source data is valid via virtual function at vtable[5]
    isValid = (this->vtable[5])(pSourceData);
    if (isValid == '\0') {
        return false;
    }

    // Try to get a free node from a pool (likely memory reuse)
    pNewNode = (int *)getFreeNodeFromPool(pSourceData); // FUN_0082b300
    if (pNewNode == (int *)0x0) {
        bFromPool = false;
        // Failed to get from pool, allocate new memory
        pMemoryManager = (void **)getMemoryManager(); // FUN_009c8f80
        int result = (**(code **)*pMemoryManager)(0x80, &stack0xfffffff0); // allocate 0x80 bytes
        if (result != 0) {
            pNewNode = (int *)allocateNewNode(); // FUN_00825340
            if (pNewNode != (int *)0x0) goto LAB_00832e10;
        }
        return false;
    }

LAB_00832e10:
    // Copy 4 integers (16 bytes) from source data into the node at offsets 0x1C-0x28
    pNewNode[7] = *pSourceData;          // +0x1C
    pNewNode[8] = pSourceData[1];        // +0x20
    pNewNode[9] = pSourceData[2];        // +0x24
    pNewNode[10] = pSourceData[3];       // +0x28

    // If we have parent data (from this->parentTransform or similar), copy 4 more ints
    pParentData = (int *)this->m_parentTransform; // offset +0x8 in this object
    if (pParentData != (int *)0x0) {
        pNewNode[15] = *(pParentData + 9);  // +0x3C (offset 0x24 in parent data)
        pNewNode[16] = *(pParentData + 10); // +0x40
        pNewNode[17] = *(pParentData + 11); // +0x44
        pNewNode[18] = *(pParentData + 12); // +0x48
    }

    // If a parent node is provided, attach to it via virtual function at vtable[1]
    if (pParentNode != (int *)0x0) {
        (**(code **)(*pNewNode + 4))(pParentNode); // newNode->setParent(pParentNode)
    }

    // If the node was newly allocated (not from pool), register it back into the pool
    if (!bFromPool) {
        registerNodeInPool(pNewNode); // FUN_008323c0
    }

    return true;
}