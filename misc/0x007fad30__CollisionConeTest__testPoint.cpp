// FUNC_NAME: CollisionConeTest::testPoint
// Role: Checks if a test point stored in this object lies inside a cone or triangle defined by the shape data.
// Address: 0x007fad30

#include <cmath>

// Constants (from global data)
const float kEpsilonSq = 1e-6f; // DAT_00e44598 - threshold for near-zero cross product magnitude
const float kNormalScale = 1.0f; // _DAT_00d5780c - scaling factor (probably 1.0 for normalization)
const float kCosThreshold = 0.0f; // _DAT_00d71d74 - cosine angle threshold (0 = 90 degrees)
const uint32 kAbsMask = 0x7FFFFFFF; // DAT_00e44680 - mask to take absolute float

// Shape types
const int SHAPE_TYPE_CONE = 4;
const int SHAPE_TYPE_OTHER = 0xB; // e.g., transform node

// Forward declarations (from engine)
struct ShapeVertexData {
    int* pVtxBuffer; // +0x00
    int type; // +0x0C
    Vector3 p1; // +0x20 (x), +0x24 (y), +0x28 (z)
    Vector3 p2; // +0x30, +0x34, +0x38
    Vector3 p3; // +0x40, +0x44, +0x48
    // Possibly more fields
};

struct CollisionConeTest {
    // +0x00 - +0x0F: unknown
    Vector3 mTestPoint; // +0x10, +0x14, +0x18 (x,y,z)
    // +0x1C - +0x27: padding
    ShapeVertexData** mShapeHandle; // +0x28: pointer to pointer to shape vertex data
    void* mTransformData; // +0x2C: used for local coordinate conversion
};

bool CollisionConeTest::testPoint() {
    ShapeVertexData* shapeData = *mShapeHandle; // double dereference to get actual vertex data
    bool result = true; // default true for non-cone shapes

    if (shapeData->type == SHAPE_TYPE_OTHER) {
        // Call a function that possibly transforms test point into local space
        // using mTransformData and fills a buffer (local_210) but we ignore output
        FUN_00aa2cd0(mTransformData, (void*)local_210); // prototype unknown, just a placeholder
    }

    if (shapeData->type == SHAPE_TYPE_CONE) {
        result = false; // assume false until proven

        // Compute two edge vectors of the triangle (cone base points)
        Vector3 edgeA = shapeData->p3 - shapeData->p2; // Ax=Ay=Az components: edgeA.y = (p3.y-p2.y), edgeA.z = (p3.z-p2.z), edgeA.x = (p3.x-p2.x)
        Vector3 edgeB = shapeData->p2 - shapeData->p1; // edgeB.x = (p2.x-p1.x), edgeB.y = (p2.y-p1.y), edgeB.z = (p2.z-p1.z)

        // Compute cross product: A x B (gives normal of the triangle)
        // Note: The decompiled code computes the negative of each component, but we compute directly for clarity.
        Vector3 normal;
        normal.x = edgeA.y * edgeB.z - edgeA.z * edgeB.y;
        normal.y = edgeA.z * edgeB.x - edgeA.x * edgeB.z;
        normal.z = edgeA.x * edgeB.y - edgeA.y * edgeB.x;

        // Squared magnitude of normal
        float magSq = normal.x * normal.x + normal.y * normal.y + normal.z * normal.z;

        if (kEpsilonSq < magSq) {
            // Normalize the normal vector
            float invMag = kNormalScale / sqrtf(magSq);
            normal.x *= invMag;
            normal.y *= invMag;
            normal.z *= invMag;

            // Dot product: our test point direction relative to cone origin? Actually this is the cosine of the angle
            // between the test point (assumed vector from some reference) and the cone's normal.
            // The test point coordinates are stored in mTestPoint.
            float dot = mTestPoint.x * normal.x + mTestPoint.y * normal.y + mTestPoint.z * normal.z;

            // Take absolute value (using bitwise AND to clear sign bit)
            float absDot = reinterpret_cast<float&>(reinterpret_cast<uint32&>(dot) & kAbsMask);

            if (kCosThreshold < absDot) {
                return true; // point is inside cone (angle less than threshold)
            }
        }
    }

    return result;
}