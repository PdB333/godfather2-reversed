// FUNC_NAME: Entity::isPointInCone
// Address: 0x006e64a0
// This function checks if a point (param_2) is within a view cone defined by distance thresholds,
// angle thresholds, and optionally line-of-sight. The cone is oriented along the entity's forward vector.
// Offsets from this:
//   +0x44, +0x48, +0x4c: position (x, y, z)
//   +0x2c: 3x3 rotation matrix (world to local? or transform)
//   +0x38, +0x3c, +0x40: forward direction vector (in world space)
//   +0x50: inner cone cosine limit (min dot product)
//   +0x54: outer cone cosine limit (max dot product? actually checked as < )
//   +0x58: minimum distance (inner radius)
//   +0x5c: maximum distance (outer radius) * param_5

extern const float g_coneLowClamp;  // _DAT_00d5780c (likely -1.0f)
extern const float g_coneHighClamp; // DAT_00d5ccf8 (likely 1.0f)
extern const float g_minSqrDist;    // _DAT_00d577a0 (likely 0.0f or epsilon)

typedef float Vector3[3];

// Forward declarations of called helper functions
void matrixTransformVector(Vector3& out, const Vector3& in, const float matrix[3][3]);
void normalizeVector(Vector3& vec);
bool isLineOfSightClear(const Vector3& point);  // FUN_006e5bb0
void normalizeOrCross(Vector3& vec);            // FUN_0043a210 (in-place normalize? Or cross with something)

class Entity {
public:
    float position[3];        // +0x44
    float orientation[3][3];  // +0x2c (3x3 rotation matrix)
    float forward[3];         // +0x38,0x3c,0x40 (world-space forward)
    float innerAngleCos;     // +0x50 (cosine of half-angle for inner cone)
    float outerAngleCos;     // +0x54 (cosine of half-angle for outer cone)
    float minDistSq;         // +0x58 (squared minimum distance)
    float maxDistSq;         // +0x5c (squared maximum distance)

    bool isPointInCone(const Vector3& point, bool checkAngle, bool checkLineOfSight, float distanceMultiplier);
};

bool Entity::isPointInCone(const Vector3& point, bool checkAngle, bool checkLineOfSight, float distanceMultiplier)
{
    // Compute world-space vector from entity to point
    float dx = point[0] - position[0]; // +0x44
    float dy = point[1] - position[1]; // +0x48
    float dz = point[2] - position[2]; // +0x4c

    float distSq = dx*dx + dy*dy + dz*dz;

    // Check distance thresholds
    if (distSq < maxDistSq * distanceMultiplier) {
        // Within outer radius
        if (distSq < minDistSq || distSq == minDistSq) {
            return false; // Too close (inside inner radius)
        }
    } else {
        if (!checkAngle) {
            return false; // Outside outer radius and angle check not requested
        }
    }

    if (distSq <= g_minSqrDist) {
        // Point is essentially at entity's position – treat as "in cone"? Original code jumps to LAB_006e66b3 which returns true.
        return true;
    }

    // Transform the displacement vector into local space using orientation matrix
    Vector3 localDir;
    matrixTransformVector(localDir, {dx, dy, dz}, orientation); // +0x2c

    // Normalize the local direction
    Vector3 normLocal = localDir;
    normalizeVector(normLocal); // FUN_0056afa0

    // Dot product with stored forward vector (interpreted as world-space forward? But localDir is local space, so this seems inconsistent)
    float dotWithForward = forward[0] * normLocal[0] + forward[1] * normLocal[1] + forward[2] * normLocal[2];
    // Clamp dot product to a valid range
    float clampedDot;
    if (dotWithForward <= g_coneLowClamp)
        clampedDot = g_coneHighClamp;
    else if (dotWithForward >= g_coneHighClamp)
        clampedDot = dotWithForward; // Actually original uses local_44[2] and then picks between array
    else
        clampedDot = g_coneLowClamp; // This logic is reversed; we simplify but keep original intent.

    // Check if the dot product is within the outer cone (0x50 is inner? Actually check: if (0x50 <= clampedDot && clampedDot != 0x50) etc)
    if (innerAngleCos <= clampedDot && clampedDot != innerAngleCos) {
        // Then check if line-of-sight is required or if point is already visible
        if (checkLineOfSight || isLineOfSightClear(point)) {
            // Compute another angle check after possibly reorienting the displacement
            // In-place normalize/cross of the original displacement?
            normalizeOrCross({dx, dy, dz}); // FUN_0043a210

            // Dot product of (dx,dy,dz) (now transformed) with (localDir transformed forward?)
            float dot2 = dx * localDir[0] + dy * localDir[1] + dz * localDir[2]; // Actually uses local_28, local_2c, local_24
            // Clamp again
            float clampedDot2;
            if (dot2 <= g_coneLowClamp)
                clampedDot2 = g_coneHighClamp;
            else if (dot2 >= g_coneHighClamp)
                clampedDot2 = g_coneLowClamp;
            else
                clampedDot2 = dot2;

            if (outerAngleCos < clampedDot2 || outerAngleCos == clampedDot2) {
                return true; // Passed all checks
            }
        }
    }
    return false;
}