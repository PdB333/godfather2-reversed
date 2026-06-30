// FUNC_NAME: CollisionSystem::rayCastTriangleSoup
int __fastcall CollisionSystem::rayCastTriangleSoup(
    ushort *indices,        // triangle index buffer (3 indices per triangle)
    float *transformMatrix, // 4x4 world transform matrix
    int vertexBuffer,       // base address of vertex buffer (stride 0x14 = 20 bytes)
    int vertexStride,       // stride between vertices (0x14)
    float *rayOrigin,       // ray origin in local space
    float (*rayDirection)[16], // ray direction (4-component, but only xyz used)
    int *hitTriangleIndex,  // output: index of closest hit triangle
    float *hitDistance,     // output: distance along ray to hit
    int outputBuffer        // output buffer for triangle data
)
{
    // Constants from data section
    float epsilon = DAT_00e2b1a4; // small epsilon (likely 0.0 or very small)
    float maxDist = DAT_00e2eff4; // maximum distance (likely large)
    float bestDist = DAT_00e2e50c; // best distance so far (initialized to max)
    
    // Extract ray origin components
    float rayX = *rayOrigin;
    float rayY = rayOrigin[1];
    float rayZ = rayOrigin[2];
    
    // Load ray direction (4 components, but only xyz used)
    float dirX = (*rayDirection)[0];
    float dirY = (*rayDirection)[1];
    float dirZ = (*rayDirection)[2];
    
    // Extract transform matrix rows (4x4)
    float m00 = transformMatrix[0];
    float m01 = transformMatrix[1];
    float m02 = transformMatrix[2];
    float m03 = transformMatrix[3];
    float m10 = transformMatrix[4];
    float m11 = transformMatrix[5];
    float m12 = transformMatrix[6];
    float m13 = transformMatrix[7];
    float m20 = transformMatrix[8];
    float m21 = transformMatrix[9];
    float m22 = transformMatrix[10];
    float m23 = transformMatrix[11];
    float m30 = transformMatrix[12];
    float m31 = transformMatrix[13];
    float m32 = transformMatrix[14];
    float m33 = transformMatrix[15];
    
    // Precompute transformed ray direction components
    float tDirX = epsilon * m30;
    float tDirY = epsilon * m31;
    float tDirZ = epsilon * m32;
    float tDirW = epsilon * m33;
    
    // Precompute transformed ray origin components
    float tRayX = epsilon * m30;
    float tRayY = epsilon * m31;
    float tRayZ = epsilon * m32;
    float tRayW = epsilon * m33;
    
    // Output buffer pointer calculation
    // param_9 + 0xc contains current count, offset by 0x601, multiplied by 0x10
    ushort *outputPtr = (ushort *)((*(ushort *)(outputBuffer + 0xc) + 0x601) * 0x10 + outputBuffer);
    ushort outputFlags = *(ushort *)(outputBuffer + 8);
    
    ushort *endIndices = indices + vertexStride * 3; // end of index buffer
    
    int currentTriangle = 0;
    int bestTriangle = -1;
    
    do {
        float scale = epsilon;
        
        // Get triangle vertex indices
        ushort idx0 = *indices;
        float *v0 = (float *)(vertexBuffer + (uint)idx0 * 0x14);
        float v0x = *v0;
        float v0y = v0[1];
        float v0z = v0[2];
        
        ushort idx1 = indices[1];
        float *v1 = (float *)(vertexBuffer + (uint)idx1 * 0x14);
        float v1x = *v1;
        float v1y = v1[1];
        float v1z = v1[2];
        
        ushort idx2 = indices[2];
        float *v2 = (float *)(vertexBuffer + (uint)idx2 * 0x14);
        float v2x = *v2;
        float v2y = v2[1];
        float v2z = v2[2];
        
        // Transform vertices to world space
        float tv0x = v0x * m00 + v0y * m10 + v0z * m20 + tRayX;
        float tv0y = v0x * m01 + v0y * m11 + v0z * m21 + tRayY;
        float tv0z = v0x * m02 + v0y * m12 + v0z * m22 + tRayZ;
        float tv0w = v0x * m03 + v0y * m13 + v0z * m23 + tRayW;
        
        float tv1x = v1x * m00 + v1y * m10 + v1z * m20 + tRayX;
        float tv1y = v1x * m01 + v1y * m11 + v1z * m21 + tRayY;
        float tv1z = v1x * m02 + v1y * m12 + v1z * m22 + tRayZ;
        float tv1w = v1x * m03 + v1y * m13 + v1z * m23 + tRayW;
        
        float tv2x = v2x * m00 + v2y * m10 + v2z * m20 + tRayX;
        float tv2y = v2x * m01 + v2y * m11 + v2z * m21 + tRayY;
        float tv2z = v2x * m02 + v2y * m12 + v2z * m22 + tRayZ;
        float tv2w = v2x * m03 + v2y * m13 + v2z * m23 + tRayW;
        
        // Compute edge vectors
        float e1x = v1x - v0x;
        float e1y = v1y - v0y;
        float e1z = v1z - v0z;
        float e2x = v2x - v0x;
        float e2y = v2y - v0y;
        float e2z = v2z - v0z;
        
        // Compute ray to vertex0 vector
        float rvx = rayX - v0x;
        float rvy = rayY - v0y;
        float rvz = rayZ - v0z;
        
        // Compute transformed triangle bounds (for AABB test)
        float minX = min(tv0x, min(tv1x, tv2x));
        float minY = min(tv0y, min(tv1y, tv2y));
        float minZ = min(tv0z, min(tv1z, tv2z));
        float maxX = max(tv0x, max(tv1x, tv2x));
        float maxY = max(tv0y, max(tv1y, tv2y));
        float maxZ = max(tv0z, max(tv1z, tv2z));
        
        // AABB test against ray
        if (minX <= epsilon && maxDist >= maxX &&
            minY <= epsilon && maxDist >= maxY &&
            minZ <= epsilon && maxDist >= maxZ)
        {
            // Store triangle data in output buffer
            *outputPtr = outputFlags;
            outputPtr[1] = (ushort)currentTriangle;
            *(uint *)(outputPtr + 2) = vertexBuffer + (uint)idx0 * 0x14;
            *(uint *)(outputPtr + 4) = vertexBuffer + (uint)idx1 * 0x14;
            *(uint *)(outputPtr + 6) = vertexBuffer + (uint)idx2 * 0x14;
            outputPtr += 8;
        }
        
        // Compute cross product of ray direction and edge2
        float crossX = e2z * dirY - e2y * dirZ;
        float crossY = e2x * dirZ - e2z * dirX;
        float crossZ = e2y * dirX - e2x * dirY;
        
        // Compute determinant
        float det = e1x * crossX + e1y * crossY + e1z * crossZ;
        
        // Backface culling and intersection test
        if (det >= DAT_00e44560) // some threshold (likely > 0)
        {
            float u = rvx * crossX + rvy * crossY + rvz * crossZ;
            if (u >= 0.0f && u <= det)
            {
                // Compute cross product of ray to vertex0 and edge1
                float crossUx = rvz * e1y - rvy * e1z;
                float crossUy = rvx * e1z - rvz * e1x;
                float crossUz = rvy * e1x - rvx * e1y;
                
                float v = dirX * crossUx + dirY * crossUy + dirZ * crossUz;
                if (v >= 0.0f && u + v <= det)
                {
                    // Compute t (distance along ray)
                    float t = (e2x * crossUx + e2y * crossUy + e2z * crossUz) * (scale / det);
                    if (t < bestDist)
                    {
                        bestTriangle = currentTriangle;
                        bestDist = t;
                    }
                }
            }
        }
        
        indices += 3;
        currentTriangle++;
        
    } while (indices != endIndices && 
             (uint)((-0x6010 - outputBuffer) + (int)outputPtr >> 4) < 0x1000);
    
    // Update output buffer count
    *(short *)(outputBuffer + 0xc) = (short)((int)outputPtr + (-0x6010 - outputBuffer) >> 4);
    
    if (bestTriangle == -1)
    {
        return 0; // no hit
    }
    
    *hitTriangleIndex = bestTriangle;
    *hitDistance = bestDist;
    return 1; // hit found
}