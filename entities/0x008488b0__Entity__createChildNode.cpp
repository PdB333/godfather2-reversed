// FUNC_NAME: Entity::createChildNode
void Entity::createChildNode() {
    // +0x78: m_pParent (pointer to parent entity)
    // +0x80: m_pFirstChild (head of child linked list)
    if (m_pParent != nullptr && m_pFirstChild == nullptr) {
        // Build an identity matrix (4x4) using a global constant (likely 1.0f)
        // local_50..uStack_14 form a 16-float matrix
        float identityMatrix[16];
        for (int i = 0; i < 16; ++i) {
            identityMatrix[i] = 0.0f;
        }
        // The decompiler shows diagonal elements set to _DAT_00d5780c (assumed 1.0f)
        identityMatrix[0]  = 1.0f; // local_50
        identityMatrix[5]  = 1.0f; // uStack_3c
        identityMatrix[10] = 1.0f; // uStack_28
        identityMatrix[15] = 1.0f; // uStack_14

        float* customTransform = nullptr; // from +0x7c
        if (m_hasCustomTransform) { // +0x18
            // Use custom translation from +0x7c (3 floats)
            customTransform = m_pCustomTransform; // +0x7c
            identityMatrix[12] = customTransform[0];
            identityMatrix[13] = customTransform[1];
            identityMatrix[14] = customTransform[2];
            // If a flags byte at +0x8 has bit 2 set, apply additional transform
            if (m_pFlagsData != nullptr && ((m_pFlagsData[0] & 4) != 0)) {
                TransformCombine(m_pFlagsData + 0x10, &identityMatrix, &identityMatrix);
            }
        } else {
            m_flags &= 0xFFFFFFF9; // +0x4 clear bits 0 and 3
            IdentityTransform(0);
            SetTranslation(0);
            MultiplyMatrix(&identityMatrix);
            SomeMatrixOp(&identityMatrix);
        }

        // Collect position data from offsets +0x84, +0x88, +0x8c, +0x90
        float posX = m_position[0];
        float posY = m_position[1];
        float posZ = m_position[2];
        float posW = m_position[3];

        int sizeOut;
        int someOutput;
        // Allocate a new node from a pool, passing the position and matrix
        int* newNodePtr = AllocateChildNode(&sizeOut, &posX, &identityMatrix,
                                            0xFFFFFFFF, 0, &someOutput);

        if (m_pFirstChild != nullptr) {
            m_pFirstChild->m_ppSelfPointer = nullptr; // clear link
            m_pFirstChild = nullptr;
        }

        int* newNode = (int*)*newNodePtr; // dereference to get actual node
        m_pFirstChild = (ChildNode*)newNode;
        if (newNode != nullptr) {
            // Node's offset +8 stores a pointer to the pointer that points to it
            // This enables efficient removal from the list
            *(int**)(newNode + 2) = &m_pFirstChild; // +8 offset = 2 ints
        }
        *newNodePtr = 0; // clear the temporary

        if (sizeOut != 0) {
            *(int*)(sizeOut + 8) = 0;
        }
    }
}