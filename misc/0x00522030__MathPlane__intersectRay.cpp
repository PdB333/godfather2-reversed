// FUNC_NAME: MathPlane::intersectRay
// Address: 0x00522030
// This function performs a ray-plane intersection test. The plane is defined by its normal vector (stored in the object as `this->normal`) and a point on the plane (`planePoint`). 
// The ray is defined by `rayOrigin` and `rayDirection`. If the ray is parallel to the plane (dot product of direction and normal is zero), returns false.
// Otherwise, computes the intersection point and stores it in `outIntersection` (with w=1) and returns true.
// Global constants: DAT_00e2b05c = 0.0f, DAT_00e2b1a4 = 1.0f

#include <cstdint>

class MathPlane {
public:
    float normal[3]; // +0x00 : plane normal vector (nx, ny, nz)

    // param_1 : outIntersection (output point, float[4])
    // param_2 : rayOrigin (float[3])
    // param_3 : rayDirection (float[3])
    // param_4 : planePoint (float[3])
    // __thiscall: ECX = this (plane normal)
    int32_t __thiscall intersectRay(float* outIntersection, float* rayOrigin, float* rayDirection, float* planePoint) {
        // Compute dot product of ray direction and plane normal
        float denom = rayDirection[0] * normal[0] + rayDirection[1] * normal[1] + rayDirection[2] * normal[2];
        if (denom == 0.0f) {
            return 0; // ray parallel to plane, no intersection
        }

        // Compute t = (planePoint - rayOrigin) dot normal / denom
        float t = ((planePoint[0] - rayOrigin[0]) * normal[0] +
                   (planePoint[1] - rayOrigin[1]) * normal[1] +
                   (planePoint[2] - rayOrigin[2]) * normal[2]) / denom;

        // Compute intersection point: rayOrigin + t * rayDirection
        outIntersection[0] = rayOrigin[0] + t * rayDirection[0];
        outIntersection[1] = rayOrigin[1] + t * rayDirection[1];
        outIntersection[2] = rayOrigin[2] + t * rayDirection[2];
        outIntersection[3] = 1.0f; // homogeneous coordinate

        return 1;
    }
};