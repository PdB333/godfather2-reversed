// FUNC_NAME: Plane::intersectRay
// Function at 0x00522030 - Computes intersection of a ray with a plane defined by normal (this) and a point on the plane.
// Returns true if intersection exists, false if ray is parallel to plane.
// Output point is stored in outPoint (4 components, w set to 1.0).

#include <cmath>

struct Plane {
    float x; // +0x00 normal X
    float y; // +0x04 normal Y
    float z; // +0x08 normal Z
    // possibly more members (not used here)
};

bool __thiscall Plane::intersectRay(const float* rayOrigin, const float* rayDir, const float* planePoint, float* outPoint) {
    // Global constants (likely 0.0f and 1.0f)
    const float zero = *reinterpret_cast<const float*>(0x00e2b05c);
    const float one  = *reinterpret_cast<const float*>(0x00e2b1a4);

    float dotNormalDir = this->x * rayDir[0] + this->y * rayDir[1] + this->z * rayDir[2];
    
    // If ray is parallel to plane (dot product zero), no intersection
    if (dotNormalDir == zero) {
        return false;
    }

    // Compute t = ( (planePoint - rayOrigin) dot normal ) / (rayDir dot normal )
    float t = (this->x * (planePoint[0] - rayOrigin[0]) +
               this->y * (planePoint[1] - rayOrigin[1]) +
               this->z * (planePoint[2] - rayOrigin[2])) / dotNormalDir;

    // Compute intersection point
    outPoint[0] = rayOrigin[0] + t * rayDir[0];
    outPoint[1] = rayOrigin[1] + t * rayDir[1];
    outPoint[2] = rayOrigin[2] + t * rayDir[2];
    outPoint[3] = one; // homogeneous coordinate set to 1.0

    return true;
}