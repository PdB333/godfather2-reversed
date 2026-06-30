// FUNC_NAME: computeTriangleNormalFromVertices

void computeTriangleNormalFromVertices(float* vertices, float* outNormal)
{
    // vertices points to 3 consecutive 4-component vectors: v0 (indices 0-2), v1 (indices 4-6), v2 (indices 8-10)
    // outNormal receives the unit normal of the triangle (v0,v1,v2) using v1-v0 and v2-v0

    float edge1x = vertices[8] - vertices[0];   // v2.x - v0.x
    float edge1y = vertices[9] - vertices[1];   // v2.y - v0.y
    float edge1z = vertices[10] - vertices[2];  // v2.z - v0.z

    float edge2x = vertices[4] - vertices[0];   // v1.x - v0.x
    float edge2y = vertices[5] - vertices[1];   // v1.y - v0.y
    float edge2z = vertices[6] - vertices[2];   // v1.z - v0.z

    // Cross product: (v1 - v0) × (v2 - v0)
    float crossX = edge2y * edge1z - edge2z * edge1y;   // local_20
    float crossY = edge2z * edge1x - edge2x * edge1z;   // local_1c
    float crossZ = edge2x * edge1y - edge2y * edge1x;   // local_18

    // Normalize the cross product in place
    normalize_vector(&crossX, &crossX);

    outNormal[0] = crossX;   // local_20
    outNormal[1] = crossY;   // local_1c
    outNormal[2] = crossZ;   // local_18
}