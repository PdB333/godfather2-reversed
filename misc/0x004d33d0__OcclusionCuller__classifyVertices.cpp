// FUNC_NAME: OcclusionCuller::classifyVertices
void OcclusionCuller::classifyVertices(float *pVertices, int vertexCount, char *pOutputMask) {
    // Global constant loaded from DAT_00e2b1a4 (likely some epsilon or scale)
    float fConst = DAT_00e2b1a4;

    // Preload 6 bytes from this object at fixed offsets (0x60, 0x120, 0x1e0, 0x2a0, 0x360, 0x420)
    // These likely represent per-cluster mask values or identifiers
    byte clusterMasks[6];
    clusterMasks[0] = *(byte *)(this + 0x60);
    clusterMasks[1] = *(byte *)(this + 0x120);
    clusterMasks[2] = *(byte *)(this + 0x1e0);
    clusterMasks[3] = *(byte *)(this + 0x2a0);
    clusterMasks[4] = *(byte *)(this + 0x360);
    clusterMasks[5] = *(byte *)(this + 0x420);

    int outputIndex = 0;
    if (vertexCount <= 0) return;

    // Iterate over input vertices (each vertex is a quad of floats: x, y, z, w?)
    for (int i = 0; i < vertexCount; i++) {
        float x = pVertices[i * 4 + 0];
        float y = pVertices[i * 4 + 1];
        float z = pVertices[i * 4 + 2];
        float w = pVertices[i * 4 + 3]; // or possibly some other component

        uint8_t combinedMask = 0;

        // Test against 6 plane clusters (each cluster provides 4 planes for a frustum side? )
        for (int cluster = 0; cluster < 6; cluster++) {
            // Pointer to the start of the cluster's plane data (each cluster is 0x30 = 48 bytes)
            // Cluster data layout (relative to cluster start):
            //   +0x00: 4 floats (plane 2? or part of previous cluster)
            //   +0x10: 4 floats (plane 3? part of this cluster)
            //   +0x20: 4 floats (plane 4? next cluster's start)
            // But due to overlap, we use indices -8 to +15 to cover 6 planes across cluster boundaries
            float *pCluster = (float *)(this + 0x20 + cluster * 0x30);

            // Compute two dot products using indices 8-11 and 12-15 (planes 5 and 6 of current cluster or 1-2 of next)
            float dot1 = pCluster[11] * fConst + pCluster[10] * z;   // using z as third coordinate
            float dot2 = pCluster[9] * y + pCluster[8] * x;
            float dot3 = pCluster[15] * fConst + pCluster[14] * z;
            float dot4 = pCluster[13] * y + pCluster[12] * x;

            // Compare w against plane equations using groups of 4 coefficients
            // Each plane is stored as 4 consecutive floats: (a, b, c, d) for a*x + b*y + c*z + d*const
            // Test 1: plane from indices -8,-7,-6,-5 (previous cluster's last plane?)
            bool t1 = w < (pCluster[-7] * y + pCluster[-8] * x + pCluster[-5] * fConst + pCluster[-6] * z);
            // Test 2: plane from indices -4,-3,-2,-1
            bool t2 = w < (pCluster[-3] * y + pCluster[-4] * x + pCluster[-1] * fConst + pCluster[-2] * z);
            // Test 3: plane from indices 0,1,2,3
            bool t3 = w < (pCluster[1] * y + pCluster[0] * x + pCluster[3] * fConst + pCluster[2] * z);
            // Test 4: plane from indices 4,5,6,7
            bool t4 = w < (pCluster[5] * y + pCluster[4] * x + pCluster[7] * fConst + pCluster[6] * z);

            // Additional two tests using the computed dot sums (interior/exterior?)
            bool t5 = w < (dot2 + dot1);  // sum of first dot product
            bool t6 = w < (dot4 + dot3);  // sum of second dot product

            // Build 4-bit mask from first 4 tests (using movmskps equivalent)
            int mask1 = (t1 ? 1 : 0) | (t2 ? 2 : 0) | (t3 ? 4 : 0) | (t4 ? 8 : 0);
            // Build 4-bit mask from last two tests (duplicated to match 4 SSE slots)
            int mask2 = (t5 ? 1 : 0) | (t6 ? 2 : 0) | (t6 ? 4 : 0) | (t5 ? 8 : 0); // note duplication

            // Combine masks: if any test in the pair passes, use the cluster's mask byte
            int combinedTests = mask1 | mask2;
            uint8_t clusterMask = (combinedTests > 0) ? 0xFF : 0x00;
            clusterMask &= clusterMasks[cluster]; // mask with per-cluster value

            combinedMask |= clusterMask;
        }

        // Write the combined mask to output array
        pOutputMask[outputIndex] = (char)combinedMask;
        outputIndex++;
    }
}