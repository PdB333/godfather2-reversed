// FUNC_NAME: ClipPolygonToPlane

int __fastcall ClipPolygonToPlane(float* verticesIn, int numVerticesIn, float* planePoint, float* verticesOut, int* outCount, float* planeNormal)
{
    // Input: verticesIn - array of 4-float vectors (each 16 bytes, x,y,z,w? w ignored)
    //        numVerticesIn - number of input vertices (must be >= 3)
    //        planePoint - point on the plane (3 floats, but passed as 4-float; 4th ignored)
    //        verticesOut - output buffer for clipped vertices (each 16 bytes)
    //        outCount - pointer to integer that will receive output vertex count
    //        planeNormal - plane normal (3 floats) passed in EDI register
    // Returns: 1 on success, 0 if invalid input or output overflow (>18 vertices)

    *outCount = 0;
    if (numVerticesIn < 3)
        return 0;

    float epsilon = DAT_00e2b1a4; // likely small tolerance for edge splitting
    float* previousVertex = verticesIn + (numVerticesIn - 1) * 4; // start with last vertex (index -1 modulo)
    int currentIndex = 0;
    bool prevInside = (planeNormal[0] * (previousVertex[0] - planePoint[0]) +
                       planeNormal[1] * (previousVertex[1] - planePoint[1]) +
                       planeNormal[2] * (previousVertex[2] - planePoint[2]) >= 0.0f);

    do {
        float* currentVertex = verticesIn + currentIndex * 4;
        // Vector from plane point to current vertex
        float vecToPoint[4] = {
            currentVertex[0] - planePoint[0],
            currentVertex[1] - planePoint[1],
            currentVertex[2] - planePoint[2],
            currentVertex[3] - planePoint[3] // w component unused in plane test
        };
        bool currentInside = (planeNormal[0] * vecToPoint[0] +
                              planeNormal[1] * vecToPoint[1] +
                              planeNormal[2] * vecToPoint[2] >= 0.0f);

        if (prevInside != currentInside) {
            // Edge crosses the plane, compute intersection point
            float edgeVec[4] = {
                currentVertex[0] - previousVertex[0],
                currentVertex[1] - previousVertex[1],
                currentVertex[2] - previousVertex[2],
                currentVertex[3] - previousVertex[3]
            };
            float edgeLenSq = edgeVec[0]*edgeVec[0] + edgeVec[1]*edgeVec[1] + edgeVec[2]*edgeVec[2];
            float t = 0.0f;
            if (DAT_00e2cbe0 < edgeLenSq) { // avoid division by zero
                t = epsilon / sqrtf(edgeLenSq);
            }
            // Scale edge vector to get intersection point
            float intersection[4];
            intersection[0] = previousVertex[0] + edgeVec[0] * t;
            intersection[1] = previousVertex[1] + edgeVec[1] * t;
            intersection[2] = previousVertex[2] + edgeVec[2] * t;
            intersection[3] = previousVertex[3] + edgeVec[3] * t;

            // Compute intersection on plane via referenced function
            ComputePlaneIntersection(previousVertex, intersection, planePoint);

            // Add intersection to output
            if (*outCount > 18) // safety check, but condition already done above
                return 0;
            float* out = verticesOut + (*outCount) * 4;
            out[0] = intersection[0];
            out[1] = intersection[1];
            out[2] = intersection[2];
            out[3] = intersection[3];
            (*outCount)++;
        }

        // If current vertex is inside, add it
        if (currentInside) {
            if (*outCount > 18)
                return 0;
            float* out = verticesOut + (*outCount) * 4;
            out[0] = currentVertex[0];
            out[1] = currentVertex[1];
            out[2] = currentVertex[2];
            out[3] = currentVertex[3];
            (*outCount)++;
        }

        prevInside = currentInside;
        previousVertex = currentVertex;
        currentIndex++;
    } while (currentIndex < numVerticesIn);

    return 1;
}