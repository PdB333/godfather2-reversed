// FUNC_NAME: NodeManager::getNodeBounds
void __thiscall NodeManager::getNodeBounds(uint32_t objId, NodeBounds& outBounds)
{
    // +0xe4: flag indicating if cached data is available (likely set when object is destroyed or moved)
    if (m_bCached) {
        // +0x13c: cached 12-byte bounds data (3 int32/float values)
        outBounds = m_cachedBounds;
        return;
    }

    // map objId to an index into the node array (size of each node = 0x1d0 = 464 bytes)
    int32_t nodeIndex = resolveNodeIndex(objId);

    // +0x10: pointer to array of NodeData structures (stride 0x1d0)
    NodeData* pNode = &m_pNodeArray[nodeIndex];

    // Copy node's 12-byte bounds data into a static scratch buffer (global DAT_01223d24)
    s_tmpBounds.m0 = pNode->x;   // first 4 bytes
    s_tmpBounds.m1 = pNode->y;   // next 4 bytes
    s_tmpBounds.m2 = pNode->z;   // bytes at offset 8

    // Store into output parameter
    outBounds = s_tmpBounds;
}