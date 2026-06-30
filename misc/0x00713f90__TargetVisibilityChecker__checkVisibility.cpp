// FUNC_NAME: TargetVisibilityChecker::checkVisibility

// Based on Ghidra decompilation at 0x00713f90.
// This function checks if a line segment (pointA to pointB) is visible/obstructed by a target object,
// given a direction vector and a scaling parameter. It uses the target's position and forward vector,
// and a global camera transform for additional frustum/cone checks.

// Assumed known types (from Godfather 2 / EARL engine):
struct Vector3 {
    float x, y, z;
};

struct Transform {
    Vector3 position; // offset +0x30 (x: +0x30, y: +0x34, z: +0x38)
    // ... other transform components
};

// Forward declarations for called functions (not fully reconstructed)
extern float g_coneMinDot; // _DAT_00d577a0
extern float g_coneMaxDot; // _DAT_00d5c458

extern void normalizeVector(Vector3* out, Vector3* in); // FUN_0056afa0
extern Transform* getGlobalCameraTransform(); // FUN_00471610 - returns a pointer
extern void computeProjection(const Vector3& in1, const Vector3& in2, const Vector3& in3, const Vector3& in4); // FUN_00712dc0
extern bool intersectLineWithShape(const Vector3& start, const Vector3& end, const Vector3& a, const Vector3& b); // FUN_0084cd10

class TargetVisibilityChecker {
public:
    // Offsets:
    // +0x10: pointer to some target (Entity*) - used for comparison
    Entity* m_currentTarget; // offset 0x10

    // param_1 = this, param_2 = pointA, param_3 = pointB, param_4 = something (time/scale), param_5 = targetObject, param_6 = direction
    int checkVisibility(const Vector3& pointA, const Vector3& pointB, float param4, Entity* targetObject, const Vector3& direction) {
        // Early exit if target is the same as stored or if target type is invalid
        if (m_currentTarget == targetObject)
            return 1; // already visible?

        int objectType = targetObject->getObjectType(); // targetObject[0x3fc] - possibly an enum
        if (objectType != 0 && objectType != 0x48)
            return 1; // not the right type, assume visible

        Vector3 targetPos;
        targetObject->getPosition(&targetPos); // vtable+0x48

        Vector3 diffA;
        diffA.x = pointA.x - targetPos.x;
        diffA.y = pointA.y - targetPos.y;
        diffA.z = pointA.z - targetPos.z;

        Vector3 diffB;
        diffB.x = pointB.x - targetPos.x;
        diffB.y = pointB.y - targetPos.y;
        diffB.z = pointB.z - targetPos.z;

        // Normalize diffB (in place)
        normalizeVector(&diffB, &diffB);

        float dotA = direction.x * diffA.x + direction.y * diffA.y + direction.z * diffA.z;
        float dotB = direction.x * diffB.x + direction.y * diffB.y + direction.z * diffB.z;

        // Check if the points are within a directional cone (defined by global min/max dot products)
        if (dotA > g_coneMinDot && dotB < g_coneMaxDot) {
            // Perform more detailed test using camera transform and object forward vector
            Transform* cameraTransform = getGlobalCameraTransform();
            Vector3 camPos = cameraTransform->position; // +0x30 (x,y), +0x38 (z)

            Vector3 forward;
            targetObject->getForwardVector(&forward); // vtable+0x4c

            // Compute some transformed coordinates (details from decompiled code)
            // The following calculations involve scaling by param4 and adding camera position components.
            float tempX = forward.z * param4 + camPos.x; // fVar4 = fStack_58 * param4 + fStack_94 (where fStack_58=forward.z? and fStack_94=camPos.x)
            // But the original code uses many stack variables; we simplify here.
            // The exact logic may be reconstructing a frustum or bounding box.

            // For the purpose of this reconstruction, we assume these are intermediate vectors for intersection test.
            Vector3 someVecA, someVecB; // not fully determined
            // The code then calls FUN_00712dc0 which likely computes a projection or axis-aligned box.
            computeProjection(someVecA, someVecB, ...); // parameters are omitted due to complexity

            // Finally, check line intersection with the shape defined by the computed vectors.
            if (intersectLineWithShape(pointA, pointB, someVecA, someVecB)) {
                return 0; // line is blocked (intersection found)
            }
        }

        return 1; // no obstruction, visible
    }
};