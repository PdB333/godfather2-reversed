// FUN_006c92e0: computeTriangleNormal (cross product of two edges and normalize)
#include <cmath>

// Assumes each point is stored contiguously as 3 floats (x,y,z) with stride 4 floats (so 16 bytes per point)
// Input: trianglePoints[0], trianglePoints[1], trianglePoints[2] (each at offsets 0, 4, 8 floats)
// Output: normalized normal stored at outNormal
void computeTriangleNormal(const float* trianglePoints, float* outNormal)
{
    float edge1X = trianglePoints[4] - trianglePoints[0]; // point1.x - point0.x
    float edge1Y = trianglePoints[5] - trianglePoints[1]; // point1.y - point0.y
    float edge1Z = trianglePoints[6] - trianglePoints[2]; // point1.z - point0.z

    float edge2X = trianglePoints[8] - trianglePoints[0]; // point2.x - point0.x
    float edge2Y = trianglePoints[9] - trianglePoints[1]; // point2.y - point0.y
    float edge2Z = trianglePoints[10] - trianglePoints[2]; // point2.z - point0.z

    // Compute cross product: edge1 × edge2
    // Note: intermediate values are stored with specific order to match original assembly
    float crossX = edge1Y * edge2Z - edge1Z * edge2Y; // corresponds to local_20
    float crossZ = edge2X * edge1Y - edge1X * edge2Y; // corresponds to local_18 (negated cross.z)
    float crossY = edge2X * edge1Z - edge1X * edge2Z; // corresponds to local_1c (negated cross.y)

    // The original stores (crossX, crossY, crossZ) into outNormal
    outNormal[0] = crossX;
    outNormal[1] = crossY;
    outNormal[2] = crossZ;

    // Normalize the vector in place (callee: 0x0056afa0)
    normalizeVector(&outNormal[0], &outNormal[0]); // assume in-place normalization function

    // After normalization, the result is written again to outNormal
    outNormal[0] = crossX;
    outNormal[1] = crossY;
    outNormal[2] = crossZ;
}

// Signature of the normalization function (inferred)
void normalizeVector(const float* input, float* output); // likely at 0x0056afa0