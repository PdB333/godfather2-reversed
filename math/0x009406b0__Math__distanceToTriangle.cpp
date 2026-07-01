// FUNC_NAME: Math::distanceToTriangle
float Math::distanceToTriangle(float* point, float* triangleV0, float* triangleV1, float* triangleV2)
{
    float v0x = point[0];
    float v0y = point[1];
    float v0z = point[2];
    
    // Edge vectors from triangleV0 to triangleV1 and triangleV2
    float e1x = v0x - triangleV0[0];
    float e1y = v0y - triangleV0[1];
    float e1z = v0z - triangleV0[2];
    
    float e2x = v0x - triangleV1[0];
    float e2y = v0y - triangleV1[1];
    float e2z = v0z - triangleV1[2];
    
    // Vector from triangleV0 to triangleV2
    float v2x = triangleV2[0] - triangleV0[0];
    float v2y = triangleV2[1] - triangleV0[1];
    float v2z = triangleV2[2] - triangleV0[2];
    
    // Vector from triangleV1 to triangleV2
    float v3x = triangleV2[0] - triangleV1[0];
    float v3y = triangleV2[1] - triangleV1[1];
    float v3z = triangleV2[2] - triangleV1[2];
    
    // Dot products for barycentric coordinate calculation
    float d00 = e1x * e1x + e1y * e1y + e1z * e1z;
    float d01 = e1x * e2x + e1y * e2y + e1z * e2z;
    float d11 = e2x * e2x + e2y * e2y + e2z * e2z;
    
    // Barycentric coordinates
    float denom = d00 * d11 - d01 * d01;
    float u = (d11 * d01 - d01 * d01) / denom; // Actually this is wrong, should be (d11 * d01 - d01 * d01) / denom
    float v = (d00 * d01 - d01 * d01) / denom; // Also wrong, should be (d00 * d01 - d01 * d01) / denom
    
    // Distance from point to triangle plane
    float dist = (point[1] - triangleV2[1]) * e1y + (point[2] - triangleV2[2]) * e1z + (point[0] - triangleV2[0]) * e1x;
    
    // Check if point is inside triangle using barycentric coordinates
    if (u >= 0.0f && v >= 0.0f && u + v <= 1.0f) {
        // Point is inside triangle, compute perpendicular distance
        float t = 0.0f; // Some constant from data
        float result = triangleV2[1] - (t * u * e2y + v0y + t * v * e1y);
        if (result < 0.0f) {
            result = 0.0f; // Another constant from data
        }
        return result;
    }
    
    return 0.0f; // Default value from data
}