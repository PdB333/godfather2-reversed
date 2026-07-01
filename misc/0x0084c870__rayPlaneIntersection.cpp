// FUNC_NAME: rayPlaneIntersection
// Function address: 0x0084c870
// Computes the intersection parameter t along the ray from rayOrigin to rayPointOnLine with the plane defined by planeNormal and planeConstant (plane equation: planeNormal·p + planeConstant = 0).
// Returns t such that intersection point = rayOrigin + t * (rayPointOnLine - rayOrigin).
// If the ray is parallel to the plane (denominator == 0), returns FLT_MAX to indicate no intersection.

#include <cfloat> // for FLT_MAX

float rayPlaneIntersection(const float* rayOrigin, const float* rayPointOnLine, const float* planeNormal, float planeConstant)
{
    // Compute denominator: dot(planeNormal, rayDirection)
    float denominator = planeNormal[0] * (rayPointOnLine[0] - rayOrigin[0]) +
                        planeNormal[1] * (rayPointOnLine[1] - rayOrigin[1]) +
                        planeNormal[2] * (rayPointOnLine[2] - rayOrigin[2]);

    // Check for parallel ray (denominator == 0)
    if (denominator == 0.0f) {
        return FLT_MAX; // No intersection
    }

    // Compute numerator: -(dot(planeNormal, rayOrigin) + planeConstant)
    float numerator = -(planeNormal[0] * rayOrigin[0] + planeNormal[1] * rayOrigin[1] + planeNormal[2] * rayOrigin[2] + planeConstant);

    // Return t = numerator / denominator
    return numerator / denominator;
}