// FUNC_NAME: Vehicle::computeForcesAndTorques
// Address: 0x007ef9c0
// This function computes force and torque vectors for a vehicle based on steering, throttle, and brake inputs.
// It uses physics data from a component (likely EngineData or VehiclePhysicsData) pointed to by pPhysicsData.
// Offsets: this+0x5e5 = m_bIsAI (if zero, add random steering noise)
//          this+0x5e2 = m_bAccelerating
//          this+0x5e0 = m_bBraking
//          pPhysicsData+0xf4 = m_fMaxSpeed
//          pPhysicsData+0xf8 = m_fEngineForce
//          pPhysicsData+0x104 = m_fSteeringForce
//          pPhysicsData+0x108 = m_fBrakeForce
//          pPhysicsData+0x10c = m_fForceMultiplier

#include <cstdint>

// Global constants (from data section)
extern float g_fDeltaTime;          // DAT_00e44748
extern float g_fMaxSpeed;           // DAT_00e44564
extern uint32_t g_uBitMask;         // DAT_00e44680 (bitmask for integer truncation)
extern float g_fTorqueMultiplier;   // DAT_00d5ef88
extern float g_fQuatW;              // DAT_00d5780c (constant for quaternion w component)

// External helper functions (from other modules)
extern float getRandomFloat();      // FUN_007f3200
extern float computeSteeringForce(float steering, float brake, float noise, float* outSteering); // FUN_007ef720
extern float computeThrottleForce(float throttle, float something, float noise, float* outBrake); // FUN_007ef7f0

void __thiscall Vehicle::computeForcesAndTorques(
    int thisVehicle,                // param_1: this pointer
    Vector3& outForce,              // param_2: output force vector (x,y,z,w)
    Vector3& outTorque,             // param_3: output torque vector (x,y,z,w)
    float& steering,                // param_4: steering input (modified)
    float& throttle,                // param_5: throttle input (modified)
    float& brake                    // param_6: brake input (modified)
)
{
    float noise;
    if (*(char*)(thisVehicle + 0x5e5) == '\0') {
        // AI controlled: add random steering noise
        noise = getRandomFloat();
    } else {
        noise = 0.0f;
    }

    float fVar3 = 0.0f;
    // Apply steering force with noise
    fVar3 = computeSteeringForce(-(steering * g_fDeltaTime), brake, noise, &steering);
    // Apply throttle/brake force
    float fVar4 = computeThrottleForce(throttle, /*extraout_EDX*/ 0, noise, &brake);

    // Get physics data pointer (from some component)
    int pPhysicsData = /*extraout_EDX_00*/ 0; // This should be derived from computeThrottleForce or similar
    // Actually the decompiled shows extraout_EDX_00 is used, likely from the second call's return.
    // For reconstruction, we assume pPhysicsData is obtained from the component.
    // In the original, it might be a member pointer. We'll assume it's stored at this+0x??.
    // Since we don't have that, we'll use a placeholder.
    // Let's assume pPhysicsData is a member of the vehicle class (e.g., this+0x??).
    // For simplicity, we'll read it from a known offset. But the decompiled doesn't show that.
    // We'll assume it's passed via the second function's return value (extraout_EDX_00).
    // In the decompiled, extraout_EDX_00 is used after the second call, so it's likely the return value of FUN_007ef7f0.
    // But that function returns float10, not a pointer. Actually the decompiled shows extraout_EDX_00 as an int.
    // This is a Ghidra artifact. We'll treat pPhysicsData as a separate pointer obtained from the vehicle.
    // For reconstruction, we'll assume it's stored at this+0x?? (e.g., this+0x4??).
    // Since we don't have that, we'll use a local variable that should be set.
    // Let's assume pPhysicsData is a member: this->m_pPhysicsData.
    // We'll define it as:
    // int pPhysicsData = *(int*)(thisVehicle + 0x???);
    // But offset unknown. We'll leave as comment.

    // For now, we'll use the decompiled's extraout_EDX_00 as pPhysicsData.
    // In the original, it's likely the return value of a function that returns a pointer.
    // We'll assume it's obtained from the second call's output.
    // Since we don't have the exact, we'll set pPhysicsData to a placeholder.
    int pPhysicsData = 0; // TODO: get from component

    float fVar5 = *(float*)(pPhysicsData + 0x10c); // m_fForceMultiplier
    throttle = throttle * g_fDeltaTime; // Scale throttle by delta time

    float fVar6 = *(float*)(pPhysicsData + 0xf8) * fVar5 * throttle; // Engine force component
    steering = (float)((uint32_t)throttle & g_uBitMask) * *(float*)(pPhysicsData + 0x108) * fVar5 + steering; // Brake force component

    // Check if vehicle is not accelerating and not braking
    if ((*(char*)(thisVehicle + 0x5e2) == '\0') && (*(char*)(thisVehicle + 0x5e0) == '\0')) {
        fVar6 = 0.0f;
        steering = 0.0f;
    }

    brake = (float)((uint32_t)throttle & g_uBitMask) * *(float*)(pPhysicsData + 0x104) * fVar5 + brake; // Steering force component
    fVar5 = g_fMaxSpeed - *(float*)(pPhysicsData + 0xf4) * fVar5 * throttle; // Speed limit component

    if ((*(char*)(thisVehicle + 0x5e2) == '\0') && (*(char*)(thisVehicle + 0x5e0) == '\0')) {
        fVar5 = 0.0f;
        brake = 0.0f;
    }

    // Write output force vector (x,y,z,w)
    outForce.x = fVar5;
    outForce.y = (float)((uint32_t)fVar5 & g_uBitMask) * g_fTorqueMultiplier + fVar4;
    outForce.z = brake;
    outForce.w = g_fQuatW;

    // Write output torque vector (x,y,z,w)
    outTorque.x = fVar6;
    outTorque.y = fVar3;
    outTorque.z = steering;
    outTorque.w = g_fQuatW;
}