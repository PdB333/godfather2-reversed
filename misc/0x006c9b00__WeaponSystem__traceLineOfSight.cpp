// FUNC_NAME: WeaponSystem::traceLineOfSight

#include <cstdint>

// Forward declarations of external functions
void normalizeVector(Vector3* vec, int unknown); // 0x009f1820
int getRotationQuaternion(); // 0x007ff880
bool rayCast(uintptr_t world, const Vector3* endPoint, void* callbackTable, int flags); // 0x009e7fd0

// External globals
extern char g_disableCollision; // at DAT_01223394 + 0x54
extern int* g_objectManager; // at DAT_012233a0
extern const float g_nearPlane; // DAT_00d5ef84
extern const float g_maxDistance; // DAT_00d5780c
extern const float g_clampDistance; // DAT_00e445dc
extern void* g_hitCallbackTable; // PTR_LAB_00d5f038

struct Vector3 {
    float x, y, z, w;
};

struct RayCastResult {
    Vector3 hitPoint;
    bool hit;
};

static RayCastResult g_rayCastResult; // set by callback

float WeaponSystem::traceLineOfSight(Vector3* from, Vector3* to, Vector3* outHit, bool useObjectRotation) {
    // Check if collision checks are globally disabled
    if (g_disableCollision != 0) {
        return 1.0f;
    }

    // Prepare ray start (homogeneous point, w=0)
    Vector3 start = *from;
    start.w = 0.0f;
    normalizeVector(&start, 0);

    // Prepare ray end
    Vector3 end = *to;
    end.w = 0.0f;

    // Unused constants (likely near/far clipping)
    float const1 = g_nearPlane;
    float const2 = g_nearPlane;

    int rotationId = 0;
    int rotationData = 0;
    if (useObjectRotation) {
        int* objPtr = *reinterpret_cast<int**>(g_objectManager + 4);
        if (objPtr != nullptr) {
            rotationId = *objPtr - 0x1f30; // offset to rotation component
            if (rotationId != 0) {
                rotationData = getRotationQuaternion();
            }
        }
    }

    // Read member fields
    int someField = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x88); // +0x88

    bool hitFlag = false;
    float clampDistance = g_clampDistance;

    // Call the raycast function with a static callback table
    // The callback writes to g_rayCastResult
    uintptr_t collisionWorld = *reinterpret_cast<uintptr_t*>(reinterpret_cast<char*>(this) + 0x84) + 0x10;
    rayCast(collisionWorld, &end, &g_hitCallbackTable, 0);

    // Copy result from global
    hitFlag = g_rayCastResult.hit;
    Vector3 hitPos = g_rayCastResult.hitPoint;

    float distance = g_maxDistance;
    if (outHit != nullptr) {
        outHit->x = 0.0f;
        outHit->y = 0.0f;
        outHit->z = 0.0f;
    }

    if (hitFlag) {
        // Clamp the distance to the maximum allowed
        if (clampDistance > 0.0f) {
            distance = (g_maxDistance < clampDistance) ? g_maxDistance : clampDistance;
        } else {
            distance = 0.0f;
        }

        if (outHit != nullptr) {
            outHit->x = hitPos.x;
            outHit->y = hitPos.y;
            outHit->z = hitPos.z;
        }
    }

    return distance;
}