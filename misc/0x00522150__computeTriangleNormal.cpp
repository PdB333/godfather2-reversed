// FUNC_NAME: computeTriangleNormal
bool __fastcall computeTriangleNormal(const float* vertices, float* outNormal)
{
    // vertices: array of 3 points, each stored as 4 floats (x, y, z, padding)
    // outNormal: output 4-component vector (x, y, z, w=0)

    // Compute edge vectors: edge1 = v1 - v0, edge2 = v2 - v0
    float edge1x = vertices[4] - vertices[0];
    float edge1y = vertices[5] - vertices[1];
    float edge1z = vertices[6] - vertices[2];
    float edge2x = vertices[8] - vertices[0];
    float edge2y = vertices[9] - vertices[1];
    float edge2z = vertices[10] - vertices[2];

    // Cross product: normal = edge1 x edge2
    outNormal[0] = edge1y * edge2z - edge1z * edge2y;
    outNormal[1] = edge1z * edge2x - edge1x * edge2z;
    outNormal[2] = edge1x * edge2y - edge1y * edge2x;
    outNormal[3] = 0.0f;

    // Compute squared length of normal
    float lenSq = outNormal[0] * outNormal[0] + outNormal[1] * outNormal[1] + outNormal[2] * outNormal[2];
    float len;
    float invLen;

    // Check against epsilon (DAT_00e2cbe0, likely ~1e-10)
    if (lenSq <= 1e-10f) {
        len = 0.0f;
        invLen = 0.0f;
    } else {
        len = sqrtf(lenSq);
        invLen = 1.0f / len; // DAT_00e2b1a4 is likely 1.0f
    }

    // Normalize the normal vector
    outNormal[0] *= invLen;
    outNormal[1] *= invLen;
    outNormal[2] *= invLen;

    // Check if triangle area (length of unnormalized normal) is above threshold (DAT_00e44598)
    if (len >= 0.001f) { // Example threshold; actual value unknown
        outNormal[3] = 0.0f;
        return true;
    }
    outNormal[3] = 0.0f;
    return false;
}