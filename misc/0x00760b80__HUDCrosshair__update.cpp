// FUNC_NAME: HUDCrosshair::update
void HUDCrosshair::update() {
    uint& flags = *(uint*)(this + 0x88);
    flags &= ~0x10; // Clear bit 4 (flag: visible)

    // Get weapon/inventory object from the crosshair owner (player)
    int* weaponObj = *(int**)(this + 0x5C);
    if (!weaponObj) return;

    int* sysPtr = retrieveSystemPointer(); // FUN_00471610
    if (!sysPtr) return;

    int weaponID = *(int*)(weaponObj + 0x5C4); // weapon type ID
    int* renderData = (int*)((char*)sysPtr + 0x30); // offset 0x30 in system

    // Initialize reticle texture slot 8 with 0,2 and scale 1.0
    initReticleTexture(weaponObj, 8, weaponID, 0, 2, 1.0f); // FUN_00760190

    // Manage a global linked list of UI nodes
    int** pGlobalList = *(int***)(gGlobalPointer + 4); // DAT_012233a0
    int* globalListNode = nullptr;
    if (pGlobalList && *pGlobalList && *pGlobalList != (int*)0x1F30) {
        globalListNode = (int*)((char*)*pGlobalList - 0x1EE8); // adjust base
    }

    // If local node differs from global, update reference
    if (m_pLocalNode != globalListNode) {
        if (m_pLocalNode) {
            releaseNode(m_pLocalNode); // FUN_004daf90
        }
        m_pLocalNode = globalListNode;
        if (globalListNode) {
            m_localNodePrev = *(int*)(globalListNode + 4);
            *(int**)(globalListNode + 4) = &m_pLocalNode;
        }
    }

    // Load texture from global string
    int* textureBuffer = nullptr;
    loadTextureFromString(renderData, &textureBuffer, gReticleTextureName); // FUN_005fcf80, _DAT_00d92d0c

    // Link first node into this object's linked list at offset 0x70
    int* firstNode = m_nodes[0]; // local_38
    if (firstNode != m_pNodeA && *m_pNodeA != firstNode) {
        if (*m_pNodeA) {
            releaseNode(m_pNodeA);
        }
        *m_pNodeA = firstNode;
        if (firstNode) {
            *(int*)(this + 0x74) = *(int*)(firstNode + 4);
            *(int**)(firstNode + 4) = m_pNodeA;
        }
    }

    // Link second node into this object's linked list at offset 0x7C
    int* secondNode = m_nodes[1]; // local_2c
    *(int*)(this + 0x78) = m_nodeData; // local_30
    if (secondNode != m_pNodeB && *m_pNodeB != secondNode) {
        if (*m_pNodeB) {
            releaseNode(m_pNodeB);
        }
        *m_pNodeB = secondNode;
        if (secondNode) {
            *(int*)(this + 0x80) = *(int*)(secondNode + 4);
            *(int**)(secondNode + 4) = m_pNodeB;
        }
    }
    *(int*)(this + 0x84) = m_nodeExtra; // local_24

    // Check if both nodes are valid
    if (*m_pNodeA == nullptr || *(int*)(this + 0x78) == nullptr) {
        // Nodes not ready, try alternative setup
        if (pGlobalList && *pGlobalList && *pGlobalList != (int*)0x1F30) {
            enableReticleTexture(weaponObj, 8, weaponID, 0); // FUN_007602f0
            int* sysData = (int*)((char*)sysPtr + 0x30);
            __int64 textureCoords = *(__int64*)((char*)sysData + 0x30); // local_58
            int textureData = *(int*)((char*)sysData + 0x38); // local_50
            loadTextureFromString(renderData, &textureBuffer, gDefaultTextureName); // DAT_00d5fcbc
            applyTextureToSlot(textureNodes); // FUN_005f7ba0
            textureBuffer = &gAltReticleTextureFunc; // PTR_FUN_00d65404
        }
        if (*m_pNodeA == nullptr || *(int*)(this + 0x78) == nullptr) {
            // Fallback: hide reticle
            resetReticleTexture(8, weaponID, 0, 1); // FUN_007600d0
            loadTextureFromString(renderData, &textureBuffer, gDefaultTextureName); // DAT_00d5fcbc
            applyTextureToSlot(textureNodes); // FUN_005f7ba0
            textureBuffer = &gFallbackTextureFunc; // PTR_LAB_00d653d4
        }
    } else {
        // Both nodes valid, set visibility flag
        flags |= 0x10;
    }

    // Clean up temporary local nodes
    if (m_pLocalNode) {
        releaseNode(m_pLocalNode);
    }
    if (m_nodes[1]) {
        releaseNode(m_nodes[1]);
    }
    if (m_nodes[0]) {
        releaseNode(m_nodes[0]);
    }
}