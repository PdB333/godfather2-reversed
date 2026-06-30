// FUNC_NAME: CollisionManager::rayCastTriangles
int __fastcall CollisionManager::rayCastTriangles(
    const ushort* triangleIndices,  // Array of triangle vertex indices (3 per triangle)
    const float* matrix,            // 4x4 transformation matrix (row-major, 16 floats)
    uintptr_t vertexBase,           // Base address of vertex data (each vertex is 20 bytes)
    int numTriangles,               // Number of triangles to test
    const float* rayOrigin,         // Ray origin (3 floats)
    const float rayDirection[4],    // Ray direction (3 floats, w is unused)
    int* outClosestTriangleIndex,   // Output: index of closest hit triangle (-1 if none)
    float* outClosestDistance,      // Output: distance to intersection point
    HitBuffer* hitBuffer            // Output buffer for all hit triangles (header + array)
    )
{
    // Load transformation matrix rows (4x4)
    float m00 = matrix[0];  float m01 = matrix[1];  float m02 = matrix[2];  float m03 = matrix[3];
    float m10 = matrix[4];  float m11 = matrix[5];  float m12 = matrix[6];  float m13 = matrix[7];
    float m20 = matrix[8];  float m21 = matrix[9];  float m22 = matrix[10]; float m23 = matrix[11];
    float m30 = matrix[12]; float m31 = matrix[13]; float m32 = matrix[14]; float m33 = matrix[15];

    // Constants (from data section; likely 0.0, 1.0, 0.0 for epsilon)
    const float kEpsilon = DAT_00e2b1a4;  // probably 0.0f (used as min bound)
    const float kOne = DAT_00e2eff4;      // probably 1.0f (used as max bound)
    const float kZero = DAT_00e44560;     // probably 0.0f (used for ray intersection denominator check)

    // Scale the last row? (seems to be multiplied by epsilon)
    float row3x = kEpsilon * m30;
    float row3y = kEpsilon * m31;
    float row3z = kEpsilon * m32;
    float row3w = kEpsilon * m33;

    // Duplicate scaled last row for later use (maybe for different vertex)
    float row3x2 = kEpsilon * m30;
    float row3y2 = kEpsilon * m31;
    float row3z2 = kEpsilon * m32;
    float row3w2 = kEpsilon * m33;

    // Additional scaled copies for other calculations
    float row3x3 = kEpsilon * m30;
    float row3y3 = kEpsilon * m31;
    float row3z3 = kEpsilon * m32;
    float row3w3 = kEpsilon * m33;

    float row3x4 = kEpsilon * m30;
    float row3y4 = kEpsilon * m31;
    float row3z4 = kEpsilon * m32;
    float row3w4 = kEpsilon * m33;

    int bestTriangleIndex = -1;      // Index of closest hit triangle
    float bestDistance = kOne;       // Distance to closest hit (initialized to 1.0)

    // Precompute end pointer for triangle indices loop
    const ushort* endIndices = triangleIndices + numTriangles * 3;

    // Get the output buffer's header values
    ushort headerFlag = *(ushort*)((uintptr_t)hitBuffer + 0x8); // +0x8: some flag
    ushort entryCount = *(ushort*)((uintptr_t)hitBuffer + 0xC); // +0xC: current number of stored entries?

    // Start writing hits to buffer; the entry area is offset by 0x6010 from hitBuffer
    uint16_t* writePtr = (uint16_t*)((uintptr_t)hitBuffer + (entryCount + 0x601) * 0x10);

    int triangleIndex = 0; // Local triangle index

    do
    {
        // Read three vertex indices for this triangle
        ushort idx0 = triangleIndices[0];
        ushort idx1 = triangleIndices[1];
        ushort idx2 = triangleIndices[2];

        // Fetch vertex positions (each vertex is 20 bytes: 3 floats for position + extra)
        float* v0 = (float*)(vertexBase + idx0 * 0x14);
        float* v1 = (float*)(vertexBase + idx1 * 0x14);
        float* v2 = (float*)(vertexBase + idx2 * 0x14);

        float v0x = v0[0], v0y = v0[1], v0z = v0[2];
        float v1x = v1[0], v1y = v1[1], v1z = v1[2];
        float v2x = v2[0], v2y = v2[1], v2z = v2[2];

        // Transform vertices by the 4x4 matrix (homogeneous coordinates)
        // Result is a 4-component vector (x,y,z,w) stored in auVar27, auVar32, auVar49 for each vertex
        // We'll compute using scalar code; originally SIMD minps/maxps are used.

        // Vertex 0 transformed
        float t0x = v0x * m00 + v0y * m10 + v0z * m20 + row3x;
        float t0y = v0x * m01 + v0y * m11 + v0z * m21 + row3y;
        float t0z = v0x * m02 + v0y * m12 + v0z * m22 + row3z;
        float t0w = v0x * m03 + v0y * m13 + v0z * m23 + row3w;

        // Vertex 1 transformed
        float t1x = v1x * m00 + v1y * m10 + v1z * m20 + row3x2;
        float t1y = v1x * m01 + v1y * m11 + v1z * m21 + row3y2;
        float t1z = v1x * m02 + v1y * m12 + v1z * m22 + row3z2;
        float t1w = v1x * m03 + v1y * m13 + v1z * m23 + row3w2;

        // Vertex 2 transformed
        float t2x = v2x * m00 + v2y * m10 + v2z * m20 + row3x3;
        float t2y = v2x * m01 + v2y * m11 + v2z * m21 + row3y3;
        float t2z = v2x * m02 + v2y * m12 + v2z * m22 + row3z3;
        float t2w = v2x * m03 + v2y * m13 + v2z * m23 + row3w3;

        // Compute edges (in object space)
        float edge1x = v1x - v0x;
        float edge1y = v1y - v0y;
        float edge1z = v1z - v0z;
        float edge2x = v2x - v0x;
        float edge2y = v2y - v0y;
        float edge2z = v2z - v0z;

        // Ray direction components (from param_6)
        float dirx = rayDirection[0];
        float diry = rayDirection[1];
        float dirz = rayDirection[2];

        // Cross product of edge2 and ray direction (for barycentric calculation)
        float cross1 = edge2y * dirz - edge2z * diry;
        float cross2 = edge2z * dirx - edge2x * dirz;
        float cross3 = edge2x * diry - edge2y * dirx;

        // Compute determinant (half of the denominator)
        float det = edge1x * cross1 + edge1y * cross2 + edge1z * cross3;

        // If determinant is near zero, skip (back-face culling? or parallel triangle)
        if (det > kZero) // DAT_00e44560
        {
            // Vector from v0 to ray origin
            float diffx = rayOrigin[0] - v0x;
            float diffy = rayOrigin[1] - v0y;
            float diffz = rayOrigin[2] - v0z;

            // Compute barycentric coordinate u
            float u = diffx * cross1 + diffy * cross2 + diffz * cross3;
            if (u >= 0.0f && u <= det)
            {
                // Compute cross product of edge1 and diff
                float cross4 = edge1y * diffz - edge1z * diffy;
                float cross5 = edge1z * diffx - edge1x * diffz;
                float cross6 = edge1x * diffy - edge1y * diffx;

                // Compute barycentric coordinate v
                float v = dirx * cross4 + diry * cross5 + dirz * cross6;
                if (v >= 0.0f && u + v <= det)
                {
                    // Compute t (distance along ray)
                    float t = (v1x * cross4 + v1y * cross5 + v1z * cross6) * (kEpsilon / det);
                    if (t < bestDistance)
                    {
                        bestDistance = t;
                        bestTriangleIndex = triangleIndex;
                    }
                }
            }
        }

        // Compute AABB for culling? The code does an AABB test before ray intersection.
        // For brevity we include the AABB logic from the original.
        // Note: The original code first checks an axis-aligned bounding box in clip space
        // (after matrix transform) before doing the ray test. We'll replicate.
        // Actually the AABB test comes before the ray intersection in the original.
        // For simplicity, we'll follow the order.

        // Compute min and max of transformed vertices (conceptually a SIMD minps/maxps)
        float minX = fminf(t0x, fminf(t1x, t2x));
        float minY = fminf(t0y, fminf(t1y, t2y));
        float minZ = fminf(t0z, fminf(t1z, t2z));
        float maxX = fmaxf(t0x, fmaxf(t1x, t2x));
        float maxY = fmaxf(t0y, fmaxf(t1y, t2y));
        float maxZ = fmaxf(t0z, fmaxf(t1z, t2z));

        // Check if the transformed triangle's AABB overlaps the clip space cube ([-1,1]^3)
        if (minX <= kEpsilon && maxX >= kOne &&
            minY <= kEpsilon && maxY >= kOne) // Note: original also checks Z? But code only checks X and Y.
        {
            // Store triangle in hit buffer
            *writePtr = headerFlag;
            writePtr[1] = (uint16_t)triangleIndex;
            *(uint32_t*)(writePtr + 2) = (uint32_t)v0;  // Store pointer to vertex 0
            *(uint32_t*)(writePtr + 4) = (uint32_t)v1;  // Store pointer to vertex 1
            *(uint32_t*)(writePtr + 6) = (uint32_t)v2;  // Store pointer to vertex 2
            writePtr += 8; // Each entry is 16 bytes (8 uint16_t)
        }

        // Advance to next triangle (3 indices)
        triangleIndices += 3;
        triangleIndex++;
    } while (triangleIndices != endIndices && (uintptr_t)((writePtr) - (uint16_t*)hitBuffer) < 0x1000 * 8); // buffer limit check

    // Update hit buffer count
    *(uint16_t*)((uintptr_t)hitBuffer + 0xC) = (uint16_t)((writePtr - (uint16_t*)hitBuffer) / 8); // number of entries stored

    // Set output parameters
    if (bestTriangleIndex != -1)
    {
        *outClosestTriangleIndex = bestTriangleIndex;
        *outClosestDistance = bestDistance;
        return (bestTriangleIndex << 8) | 1; // Return index in upper bits and hit flag in LSB
    }
    else
    {
        return (bestTriangleIndex << 8); // no hit: return 0xFFFFFF00
    }
}