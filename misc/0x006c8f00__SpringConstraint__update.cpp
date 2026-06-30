// FUNC_NAME: SpringConstraint::update
// Address: 0x006c8f00
// Role: Updates a spring constraint that limits the distance between a target and a position,
//       with internal state for spring dynamics. Used for camera or object following.

#include <cmath>

// Forward declarations for external functions
extern void clampVectorLength(float* vec, float* vecOut, int flag, float maxLength);
extern void fpSetup1(); // FUN_00b9be2b - floating-point setup
extern void fpSetup2(); // FUN_00b9a9fa - floating-point setup

// Global constants (from data references)
extern float g_oneMinusSomething; // DAT_00e44564 - likely 1.0f
extern float g_springConstant;    // DAT_00e445c8
extern float g_velocityScale;     // DAT_00e44748
extern bool g_useAlternateMode;   // DAT_0112a7a5 - byte flag

struct Vector3 {
    float x, y, z;
};

class SpringConstraint {
public:
    // Offsets:
    // +0x94: m_internalPos (float) - internal spring position (distance)
    // +0x98: m_internalVel (float) - internal spring velocity
    float m_internalPos;
    float m_internalVel;

    void update(float stiffness, float damping, float param4, float param5,
                const Vector3& target, Vector3& position, Vector3& velocityOut) {
        float fVar4;
        if (!g_useAlternateMode) {
            fVar4 = g_oneMinusSomething - stiffness * param4 * g_springConstant;
        } else {
            fVar4 = stiffness * param4 * g_springConstant;
        }

        // Spring dynamics on internal state
        float fVar1 = m_internalPos - fVar4; // difference from target distance
        float fVar2 = (fVar1 * param5 + m_internalVel) * damping; // spring force with damping
        double dVar3 = static_cast<double>(g_oneMinusSomething - damping * param5); // damping factor

        fpSetup1(); // floating-point setup

        // Update internal state
        m_internalPos = fVar4 + (fVar2 + fVar1) * static_cast<float>(dVar3);
        m_internalVel = (m_internalVel - fVar2 * param5) * static_cast<float>(dVar3);

        // Compute difference vector between current position and target
        Vector3 diff;
        diff.x = position.x - target.x;
        diff.y = position.y - target.y;
        diff.z = position.z - target.z;

        // Clamp the difference vector to the maximum distance fVar4
        int flag = 0;
        clampVectorLength(&diff.x, &diff.x, flag, fVar4);

        // Update position to target + clamped difference
        position.x = target.x + diff.x;
        position.y = target.y + diff.y;
        position.z = target.z + diff.z;

        fpSetup2(); // floating-point setup

        // Compute output velocity (2D in x-y plane)
        velocityOut.x = diff.y * g_velocityScale; // note: uses y component
        velocityOut.y = (g_oneMinusSomething - diff.x) * g_velocityScale; // uses x component
        velocityOut.z = 0.0f;
    }
};