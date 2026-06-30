// FUN_00521dd0: GeometryUtils::clipConvexPolygonToPlane
int __fastcall clipConvexPolygonToPlane(const float* inputVertices, int vertexCount, const float* planePoint, float* outputVertices)
{
    float* outCount; // unaff_ESI - pointer to output vertex count (caller provides)
    const float* planeNormal; // unaff_EDI - pointer to plane normal (set by caller before call)
    float epsilon = DAT_00e2b1a4; // small epsilon for intersection? (unused in this version)
    float maxDistSq = DAT_00e2cbe0; // squared distance threshold for intersection

    *outCount = 0;
    if (vertexCount < 3) {
        return 0;
    }

    // Initialize first edge: from last vertex to first vertex
    int prevIndex = (vertexCount - 1) * 4; // index of last vertex in float array (4 floats per vertex)
    bool prevInside = (planeNormal[0] * (inputVertices[prevIndex] - planePoint[0]) +
                      planeNormal[1] * (inputVertices[prevIndex + 1] - planePoint[1]) +
                      planeNormal[2] * (inputVertices[prevIndex + 2] - planePoint[2])) >= 0.0f;

    int currentIndex = 0; // index in input array
    int i = 0;
    do {
        // Check max output vertices (18 vertices max for a convex polygon?)
        if (*outCount > 0x12) {
            return 0;
        }

        // If previous vertex was inside, output it
        if (prevInside) {
            float* src = (float*)(inputVertices + prevIndex);
            float* dst = outputVertices + (*outCount) * 4;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            (*outCount)++;
        }

        // Current vertex position relative to plane
        float diffX = inputVertices[currentIndex] - planePoint[0];
        float diffY = inputVertices[currentIndex + 1] - planePoint[1];
        float diffZ = inputVertices[currentIndex + 2] - planePoint[2];

        bool currentInside = (planeNormal[0] * diffX +
                             planeNormal[1] * diffY +
                             planeNormal[2] * diffZ) >= 0.0f;

        // If sign changed, we need to clip the edge
        if (prevInside != currentInside) {
            // Edge vector from previous to current vertex
            float edgeX = inputVertices[currentIndex] - inputVertices[prevIndex];
            float edgeY = inputVertices[currentIndex + 1] - inputVertices[prevIndex + 1];
            float edgeZ = inputVertices[currentIndex + 2] - inputVertices[prevIndex + 2];
            float edgeLenSq = edgeX * edgeX + edgeY * edgeY + edgeZ * edgeZ;

            float t = 0.0f;
            if (edgeLenSq > maxDistSq) {
                t = epsilon / sqrtf(edgeLenSq); // scale factor based on epsilon
            }
            edgeX *= t;
            edgeY *= t;
            edgeZ *= t;

            // Compute intersection point (delegated to helper function)
            float intersectionPoint[4];
            FUN_00522030(inputVertices + prevIndex, &edgeX, planePoint); // modifies intersectionPoint
            // Output intersection point
            float* dst = outputVertices + (*outCount) * 4;
            dst[0] = intersectionPoint[0];
            dst[1] = intersectionPoint[1];
            dst[2] = intersectionPoint[2];
            dst[3] = intersectionPoint[3];
            (*outCount)++;
        }

        // Move to next edge
        prevInside = currentInside;
        prevIndex = currentIndex;
        currentIndex += 4; // stride of 4 floats per vertex
        i++;
    } while (i < vertexCount);

    return 1;
}