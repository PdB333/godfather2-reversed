// FUNC_NAME: Sphere::clipToFrustum

#include <cstdint>

// Constants from globals (likely defined elsewhere)
extern const float kFarClipDistance;   // DAT_00e44564
extern const float kResponseFactor1;   // DAT_00e2b1a4
extern const float kResponseFactor2;   // DAT_00e2b04c

struct Plane {
    float nx;
    float ny;
    float nz;
    float d;        // signed distance from origin
};

struct Sphere {
    float x, y, z; // center
    float radius;  // +0x0C

    // Returns 0: fully inside, 1: clipped to far plane, 2: completely outside frustum
    int __thiscall clipToFrustum(const Sphere& src, const Plane* planes) {
        // Copy source sphere into this object
        this->x = src.x;
        this->y = src.y;
        this->z = src.z;
        this->radius = src.radius;

        int insideCount = 0;
        for (int i = 0; i < 6; ++i) {
            const Plane& plane = planes[i];
            // Signed distance from sphere center to plane (dot + d)
            float dist = plane.nx * this->x + plane.ny * this->y + plane.nz * this->z + plane.d;

            // Completely outside (no intersection)
            if (this->radius < dist) {
                return 2;
            }

            // Check if sphere is close to the far clipping plane (where kFarClipDistance acts as threshold)
            // If the distance is greater than or equal to (kFarClipDistance - radius), we need to clip.
            if (kFarClipDistance - this->radius <= dist) {
                // Penetration ratio relative to radius and response factor
                float penetrationRatio = (this->radius - dist) / (this->radius * kResponseFactor2);
                // New position adjustment factor along plane normal
                float adjustFactor = kFarClipDistance - (kResponseFactor1 - penetrationRatio) * this->radius;

                // Push sphere back along plane normal and shrink radius
                this->x += adjustFactor * (-plane.nx);  // note: normal direction reversed? Actually code uses pfVar7[-1] etc.
                this->y += adjustFactor * (-plane.ny);
                this->z += adjustFactor * (-plane.nz);
                this->radius = penetrationRatio * this->radius;
            } else {
                ++insideCount;
            }
        }

        // Return 0 if all planes were inside without adjustment, 1 otherwise
        return (insideCount != 6) ? 1 : 0;
    }
};