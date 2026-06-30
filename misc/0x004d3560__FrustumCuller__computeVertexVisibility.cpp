// FUNC_NAME: FrustumCuller::computeVertexVisibility
void __thiscall FrustumCuller::computeVertexVisibility(void *vertexBuffer, char *outMasks, int vertexCount)
{
    // Global scale factor (likely plane distance offset)
    const float zNearOffset = DAT_00e2b1a4;

    // Per-plane enable masks loaded from this+0x60, etc. (7 planes, stride 0xC0)
    byte planeEnableMasks[7];
    planeEnableMasks[0] = *(byte *)((uint)this + 0x60);
    planeEnableMasks[1] = *(byte *)((uint)this + 0x120);
    planeEnableMasks[2] = *(byte *)((uint)this + 0x1e0);
    planeEnableMasks[3] = *(byte *)((uint)this + 0x2a0);
    planeEnableMasks[4] = *(byte *)((uint)this + 0x360);
    planeEnableMasks[5] = *(byte *)((uint)this + 0x420);
    planeEnableMasks[6] = *(byte *)((uint)this + 0x4e0);

    // Vertex data begins at offset 8 inside vertexBuffer (e.g., after header)
    float *vertexData = (float *)((char *)vertexBuffer + 8);
    int written = 0;

    if (vertexCount > 0)
    {
        do
        {
            // Current vertex (x, y, z, w)
            float vx = vertexData[-2];
            float vy = vertexData[-1];
            float vz = vertexData[0];
            float vw = vertexData[1];

            uint combinedMask = 0;
            int planeIndex = 0;

            // Iterate over 7 frustum planes
            float *planeData = (float *)((uint)this + 0x20); // base of plane matrices, stride 0x30 per plane
            do
            {
                // Transform vertex using plane matrix (partial multiply)
                float t1 = planeData[11] * zNearOffset + planeData[10] * vz;
                float t2 = planeData[9]  * vy + planeData[8]  * vx;
                float t3 = planeData[15] * zNearOffset + planeData[14] * vz;
                float t4 = planeData[13] * vy + planeData[12] * vx;

                // Evaluate four clip distances (using plane data from offset -8..-1 = first 8 floats)
                // These compare vw against dot products with (vx,vy,zNearOffset,vz) components
                uint mask1 = 0;
                mask1 |= (vw < planeData[-7] * vy + planeData[-8] * vx + planeData[-5] * zNearOffset + planeData[-6] * vz) ? 8 : 0;
                mask1 |= (vw < planeData[-3] * vy + planeData[-4] * vx + planeData[-1] * zNearOffset + planeData[-2] * vz) ? 4 : 0;
                mask1 |= (vw < planeData[5]  * vy + planeData[4]  * vx + planeData[7]  * zNearOffset + planeData[6]  * vz) ? 2 : 0;
                mask1 |= (vw < planeData[1]  * vy + planeData[0]  * vx + planeData[3]  * zNearOffset + planeData[2]  * vz) ? 1 : 0;

                // Two additional tests using transformed distances
                uint mask2 = 0;
                mask2 |= (vw < t2 + t1) ? 4 : 0;
                mask2 |= (vw < t4 + t3) ? 8 : 0;
                mask2 |= (vw < t4 + t3) ? 2 : 0;  // duplicate?
                mask2 |= (vw < t2 + t1) ? 1 : 0;

                // Combine and mask with per-plane enable
                byte planeMask = planeEnableMasks[planeIndex];
                if (mask1 || mask2)
                    combinedMask |= planeMask;

                planeIndex++;
                planeData += 12; // stride 0x30 in bytes (12 floats)
            } while (planeIndex < 7);

            // Store result byte
            outMasks[written] = (char)combinedMask;

            written++;
            vertexData += 4;   // advance to next vertex (4 floats)
        } while (written < vertexCount);
    }
}