// FUNC_NAME: ChaseCamera::computeDesiredPosition
#include <cstdint>

struct Vector3 {
    float x;
    float y;
    float z;
};

// Internal math functions
int __fastcall checkLineIntersection(const Vector3& a, const Vector3& b, int mode, int flag, float height);
Vector3* __fastcall computeSteeringVector(Vector3& out, const Vector3& a, const Vector3& b, int result, int flag, int, int, float timeStep);

// 0x005f6460
// This function computes a projected or follow position on a surface/path.
// It takes:
//   [EAX] = this: pointer to a structure containing current position (Vector3 at +0, +4, +8)
//   [ESI] = goal: pointer to target position
//   [EDI] = someFlag: an int modifier (e.g., mode or clamp flag)
//   param_2: output vector (Vector3)
//   param_3: time step / parameter for interpolation
// Returns: param_2 (same pointer)
__thiscall Vector3* ChaseCamera::computeDesiredPosition(const Vector3& goal, Vector3& out, int someFlag, float timeStep)
{
    // this->position (Vector3 at offsets +0, +4, +8)
    const Vector3& currentPos = *(Vector3*)this;

    // Local copies for intermediate computation
    Vector3 localA = currentPos;          // x,z from this
    Vector3 localB = goal;                // x,z from goal (y overwritten later)

    // Run intersection/line check: compare currentPos's XZ plane with goal's XZ plane,
    // using currentPos.y as height reference and someFlag as extra parameter
    int intersectResult = checkLineIntersection(localA, localB, 0, someFlag, currentPos.y);

    if (intersectResult != 0)
    {
        // Compute steering or projection vector into temporary storage
        Vector3 tempResult;
        Vector3* pTemp = computeSteeringVector(tempResult, localA, localB, intersectResult, someFlag, 0, 0, timeStep);
        // Copy the computed X and Z from the result
        localB.x = pTemp->x;
        localB.z = pTemp->z;
        // Note: localB.y is from the original goal (kept unchanged)
    }

    // Build output: keep goal's Y, overwrite X and Z with computed values (or original if not computed)
    out.x = localB.x;
    out.y = goal.y;           // +0x04 from ESI
    out.z = localB.z;

    return &out;
}