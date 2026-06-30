// FUNC_NAME: CollisionManager::sweptTriangleCollisionTest
uint* CollisionManager::sweptTriangleCollisionTest(int* thisPtr, float deltaTime, float radiusThreshold)
{
    // +0x12743: number of triangles in collision mesh (ushort)
    // +0x13f46: start of triangle data array (each entry: 4 ints? 16 bytes)
    if (!FUN_0066def0()) // isCollisionEnabled
        return nullptr;

    uint triangleCount = *(ushort*)(thisPtr + 0x12743);
    int currentSphereId = 0;
    if (triangleCount != 0) {
        int* triangleDataIter = thisPtr + 0x13f46;
        // Global constants (likely timestep, epsilon)
        float invDt = DAT_00e44628; // could be 1.0f / deltaTime or similar

        float pointPosX = 0.0f, pointPosY = 0.0f, pointPosZ = 0.0f; // initialized but overwritten
        float prevDistToPlane = 0.0f;

        do {
            // Index into array of sphere/point data: +0x12944 gives entity index, +0x12744 gives pointer to triangle block
            int sphereIndex = *(ushort*)(triangleDataIter - 2); // first ushort in entry
            int sphereEntity = thisPtr[sphereIndex + 0x12944];
            int triangleBlock = thisPtr[sphereIndex + 0x12744];
            int someOffset = *(int*)(triangleBlock + 0x50); // base pointer for triangle data

            if (sphereEntity != currentSphereId) {
                // Cache plane equation for new sphere
                float globalPointY = DAT_00e44564; // likely a global world point Y (or height)
                // Call to FUN_00417560 maybe updates global state?
                FUN_00417560(); // maybe get current time?

                // +0x90, +0x94, +0x98: sphere position
                // +0x80, +0x84, +0x88: sphere velocity
                float spherePosX = *(float*)(sphereEntity + 0x90);
                float spherePosY = *(float*)(sphereEntity + 0x94);
                float spherePosZ = *(float*)(sphereEntity + 0x98);
                float sphereVelX = *(float*)(sphereEntity + 0x80);
                float sphereVelY = *(float*)(sphereEntity + 0x84);
                float sphereVelZ = *(float*)(sphereEntity + 0x88);

                // Compute predicted position after deltaTime
                float predPosX = globalPointY - spherePosX;
                float predPosY = globalPointY - spherePosY;
                float predPosZ = globalPointY - spherePosZ;
                // Compute signed distance from plane (with motion)
                float distToPlane = globalPointY - (
                    (deltaTime * sphereVelX + spherePosX) * predPosX +
                    (deltaTime * sphereVelY + spherePosY) * predPosY +
                    (deltaTime * sphereVelZ + spherePosZ) * predPosZ
                );
                prevDistToPlane = distToPlane;
                currentSphereId = sphereEntity;
                pointPosX = predPosX;
                pointPosY = predPosY;
                pointPosZ = predPosZ;
            }

            // Load triangle vertices (each is 4 floats, but only xyz used; w ignored)
            float* v0 = (float*)triangleDataIter[-1];
            float* v1 = (float*)*triangleDataIter;
            float* v2 = (float*)triangleDataIter[1];

            float e0_x = v1[0] - v0[0];
            float e0_y = v1[1] - v0[1];
            float e0_z = v1[2] - v0[2];
            float e1_x = v2[0] - v0[0];
            float e1_y = v2[1] - v0[1];
            float e1_z = v2[2] - v0[2];
            float e2_x = v1[0] - v2[0];
            float e2_y = v1[1] - v2[1];
            float e2_z = v1[2] - v2[2];

            // Cross product of e0 and e1 (triangle normal * 2)
            float normalX = e1_y * e0_z - e1_z * e0_y;
            float normalY = e1_z * e0_x - e1_x * e0_z;
            float normalZ = e1_x * e0_y - e1_y * e0_x;

            // Scale factor from global constants (likely 1.0f / triangle area or similar)
            float scaledNormalX = normalX * invDt;
            float scaledNormalY = normalY * invDt;
            float scaledNormalZ = normalZ * invDt;

            // Compute barycentric coordinates or distance projection
            float dotProd = scaledNormalX * pointPosX + scaledNormalY * pointPosY + scaledNormalZ * pointPosZ;

            // Magnitude of normal (twice triangle area)
            float areaSq = normalX * normalX + normalY * normalY + normalZ * normalZ;
            float area = 0.0f, invArea = 0.0f;
            if (areaSq <= DAT_00e2cbe0) { // epsilon for degenerate triangle
                area = 0.0f;
                invArea = 0.0f;
            } else {
                area = sqrtf(areaSq);
                invArea = DAT_00e2b1a4 / area; // DAT_00e2b1a4 likely 1.0f
            }

            // Check if triangle is large enough and sphere is within distance threshold
            if (DAT_00e44598 <= area && 
                radiusThreshold <= (normalX * invArea * pointPosX + normalY * invArea * pointPosY + normalZ * invArea * pointPosZ))
            {
                // Compute distance from plane using clipped values
                float d0 = (float)((uint)(v0[1] * pointPosX + v0[2] * pointPosY + v0[0] * pointPosZ + prevDistToPlane) & (uint)DAT_00e44680);
                float d1 = (float)((uint)(v1[1] * pointPosX + v1[2] * pointPosY + v1[0] * pointPosZ + prevDistToPlane) & (uint)DAT_00e44680);
                float d2 = (float)((uint)(v2[1] * pointPosX + v2[2] * pointPosY + v2[0] * pointPosZ + prevDistToPlane) & (uint)DAT_00e44680);

                // Find minimum distance
                float minDist = d0;
                if (d1 < minDist) minDist = d1;
                if (d2 < minDist) minDist = d2;

                if (minDist <= DAT_00e2fc48) { // collision threshold
                    // Index into triangle buffer (+0x88) using ushort at (triangleDataIter-6)
                    ushort* triIdx = (ushort*)(triangleDataIter - 3); // -6 bytes due to ushort alignment
                    ushort idx0 = triIdx[0];
                    ushort idx1 = triIdx[1];
                    ushort idx2 = triIdx[2];
                    int basePtr = *(int*)(triangleBlock + 0x88);
                    ushort* vertexPtr = (ushort*)(basePtr + (uint)*(ushort*)((int)triangleDataIter - 6) * 6);
                    // FUN_0066e060: compute triangle data (e.g., barycentric coordinates, hit point)
                    FUN_0066e060(
                        (triangleBlock - *(int*)(someOffset + 0x50)) / 0xb0, // maybe triangle index
                        idx0, idx1, idx2,
                        &v0, &v1, &v2 // output transformed vertices? Actually passed as float*
                    );
                }
            }
            triangleDataIter += 4;
            triangleCount--;
        } while (triangleCount != 0);
    }

    // Update collision counters and return hit info
    uint* hitInfo = (uint*)thisPtr[4];
    uint* result = nullptr;
    if (hitInfo != nullptr && hitInfo[3] != 0) {
        *hitInfo |= 1; // mark as used
        thisPtr[1] += hitInfo[3]; // increment hit count
        *thisPtr += 1; // increment total collision count
        result = hitInfo;
    }
    thisPtr[4] = 0; // clear current hit info
    return result;
}