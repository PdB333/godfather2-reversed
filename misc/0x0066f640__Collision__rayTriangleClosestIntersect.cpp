// FUNC_NAME: Collision::rayTriangleClosestIntersect
bool __thiscall Collision::rayTriangleClosestIntersect(int triangleCount, float* vertexBuffer, float* rayOrigin, float* rayDirection, int* outTriangleIndex, float* outDistance)
{
    // in_EAX is a pointer to triangle index array (ushort[3*triangleCount]), passed via EAX
    ushort* indexPtr = reinterpret_cast<ushort*>(in_EAX);
    ushort* endPtr = indexPtr + triangleCount * 3;

    float bestDistance = kInitialLargeDistance; // 0x00e2e50c
    int bestTriangle = -1;

    // Ray direction (first 3 floats from rayDirection param)
    float dx = rayDirection[0];
    float dy = rayDirection[1];
    float dz = rayDirection[2];

    while (indexPtr != endPtr)
    {
        // Vertex indices for this triangle
        int idx0 = *indexPtr;
        int idx1 = indexPtr[1];
        int idx2 = indexPtr[2];

        // Vertex positions (stride 0x14)
        float* v0 = reinterpret_cast<float*>(vertexBuffer + idx0 * 0x14);
        float* v1 = reinterpret_cast<float*>(vertexBuffer + idx1 * 0x14);
        float* v2 = reinterpret_cast<float*>(vertexBuffer + idx2 * 0x14);

        float ax = v0[0], ay = v0[1], az = v0[2];
        float bx = v1[0], by = v1[1], bz = v1[2];
        float cx = v2[0], cy = v2[1], cz = v2[2];

        // Ray origin
        float ox = rayOrigin[0], oy = rayOrigin[1], oz = rayOrigin[2];

        // Vectors: edge1 = b - a, edge2 = c - a
        float e1x = bx - ax, e1y = by - ay, e1z = bz - az;
        float e2x = cx - ax, e2y = cy - ay, e2z = cz - az;

        // Vector from vertex a to ray origin: tvec = ox - ax, etc.
        float tvecx = ox - ax, tvecy = oy - ay, tvecz = oz - az;

        // Compute determinant and inverse
        // cross(rayDir, edge2)
        float pvecx = dy * e2z - dz * e2y;
        float pvecy = dz * e2x - dx * e2z;
        float pvecz = dx * e2y - dy * e2x;

        // Determinant: dot(edge1, pvec)
        float det = e1x * pvecx + e1y * pvecy + e1z * pvecz;

        // Early out if degenerate (small epsilon)
        if (det <= kDeterminantEpsilon) // 0x00e44560
        {
            indexPtr += 3;
            continue;
        }

        // Barycentric coordinate u = dot(tvec, pvec) / det
        float u = tvecx * pvecx + tvecy * pvecy + tvecz * pvecz;
        if (u < 0.0f || u > det)
        {
            indexPtr += 3;
            continue;
        }

        // cross(tvec, edge1)
        float qvecx = tvecy * e1z - tvecz * e1y;
        float qvecy = tvecz * e1x - tvecx * e1z;
        float qvecz = tvecx * e1y - tvecy * e1x;

        // Barycentric coordinate v = dot(rayDir, qvec) / det
        float v = dx * qvecx + dy * qvecy + dz * qvecz;
        if (v < 0.0f || u + v > det)
        {
            indexPtr += 3;
            continue;
        }

        // Distance along ray t = dot(edge2, qvec) / det
        float t = e2x * qvecx + e2y * qvecy + e2z * qvecz;
        // Scale by constant (likely 1.0 / det)
        t = t * (kDistanceScale / det); // 0x00e2b1a4

        // Update closest
        if (t < bestDistance)
        {
            bestDistance = t;
            bestTriangle = (indexPtr - reinterpret_cast<ushort*>(in_EAX)) / 3; // triangle index
        }

        indexPtr += 3;
    }

    if (bestTriangle == -1)
    {
        return false;
    }
    *outTriangleIndex = bestTriangle;
    *outDistance = bestDistance;
    return true;
}