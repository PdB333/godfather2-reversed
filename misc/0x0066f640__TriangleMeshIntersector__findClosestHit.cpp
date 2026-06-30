// FUNC_NAME: TriangleMeshIntersector::findClosestHit
int __thiscall TriangleMeshIntersector::findClosestHit(
    int triangleCount,                // number of triangles
    ushort* indexBuffer,              // triangle indices (3 per triangle, EAX register)
    float* vertexPositions,           // base of vertex array (stride 0x14 = 20 bytes = 5 floats)
    float* rayOrigin,                 // ray origin (x, y, z)
    float rayDirection[3],            // ray direction (packed in 16-byte parameter, only 3 used)
    int* outTriangleIndex,            // returns index of closest triangle in the buffer
    float* outDistance                // returns distance along ray to intersection
)
{
    float denom, u, v, t;
    float minT = DAT_00e2e50c;        // initial large distance (likely FLT_MAX)
    int closestIndex = -1;

    // iterate over all triangles (each triangle uses 3 consecutive ushort indices)
    ushort* end = indexBuffer + triangleCount * 3;
    for (int i = 0; indexBuffer != end; indexBuffer += 3, i++)
    {
        // Load triangle vertices from vertex buffer (stride = 0x14 = 20 bytes => 5 floats)
        float* v0 = (float*)(vertexPositions + (uint)indexBuffer[0] * 0x14);
        float* v1 = (float*)(vertexPositions + (uint)indexBuffer[1] * 0x14);
        float* v2 = (float*)(vertexPositions + (uint)indexBuffer[2] * 0x14);

        // Edges and difference
        float e1x = v1[0] - v0[0];
        float e1y = v1[1] - v0[1];
        float e1z = v1[2] - v0[2];

        float e2x = v2[0] - v0[0];
        float e2y = v2[1] - v0[1];
        float e2z = v2[2] - v0[2];

        float Tx = rayOrigin[0] - v0[0];
        float Ty = rayOrigin[1] - v0[1];
        float Tz = rayOrigin[2] - v0[2];

        // Cross product: h = rayDirection × e2
        float hx = rayDirection[1] * e2z - rayDirection[2] * e2y;
        float hy = rayDirection[2] * e2x - rayDirection[0] * e2z;
        float hz = rayDirection[0] * e2y - rayDirection[1] * e2x;

        // Denominator: a = dot(e1, h)
        denom = e1x * hx + e1y * hy + e1z * hz;

        // If denom is near zero, ray is parallel (skip)
        if (denom < DAT_00e44560)      // likely 0.0f or epsilon
            continue;

        // u = dot(T, h) / denom
        u = Tx * hx + Ty * hy + Tz * hz;
        if (u < 0.0f || u > denom)     // note: compare against denom, not 1
            continue;

        // Cross product: q = T × e1
        float qx = Ty * e1z - Tz * e1y;
        float qy = Tz * e1x - Tx * e1z;
        float qz = Tx * e1y - Ty * e1x;

        // v = dot(rayDirection, q) / denom
        v = rayDirection[0] * qx + rayDirection[1] * qy + rayDirection[2] * qz;
        if (v < 0.0f || u + v > denom)
            continue;

        // Compute t = dot(e2, q) / denom (scaled by constant)
        t = e2x * qx + e2y * qy + e2z * qz;
        t = t * (DAT_00e2b1a4 / denom); // likely 1.0f, so t = dot(e2,q)/denom
        if (t < minT)
        {
            minT = t;
            closestIndex = i;
        }
    }

    if (closestIndex == -1)
    {
        return 0;   // no intersection
    }

    *outTriangleIndex = closestIndex;
    *outDistance = minT;
    return 1;
}