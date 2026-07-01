// FUNC_NAME: Entity::updateTargetTransform

// Reconstructed from Ghidra at 0x00900ec0
// This function updates a target transform (position/rotation) for an entity,
// scaling by a global time factor and clearing a previous target if present.

#include <cstdint>

// Forward declarations for called functions (not provided)
extern float* getCurrentTime(); // FUN_00471610 - returns pointer to time?
extern void getTransform(int obj, float* outPos, float* outRot); // FUN_004bffa0
extern void setTargetTransform(void* entity, void* targetPtr, float* pos, float* rot, int obj, int mode); // FUN_00850e80

// Global time scale factor (from _DAT_00d5c458)
extern float g_timeScale;

// Global constant (likely identity quaternion or zero vector, from _DAT_00d5780c)
extern float g_identityQuat[4]; // or just a float constant

void __fastcall Entity::updateTargetTransform(int this) // param_1 = this
{
    // Offset +0x184: pointer to a previous target transform (or resource)
    int* targetPtr = *(int**)(this + 0x184);
    if (targetPtr != nullptr)
    {
        // Release/cleanup previous target
        FUN_009008a0(); // likely release function
        FUN_009f01a0(); // likely cleanup function
        *(int**)(this + 0x184) = nullptr;
    }

    // Get current time or frame index
    int currentTime = FUN_00471610(); // returns some time/object handle

    // Extract position and rotation from the time object
    float localPos[3]; // local_3c, local_38, local_34
    float localRot[4]; // local_30, local_2c, local_28, local_24 (quaternion)
    FUN_004bffa0(&localPos, currentTime); // fills localPos and localRot? Actually signature: FUN_004bffa0(&local_3c, iVar1) - but local_3c is first float of pos, and local_30 etc are set later. So likely the function fills both arrays.

    // Scale position by global time factor
    localPos[0] *= g_timeScale;
    localPos[1] *= g_timeScale;
    localPos[2] *= g_timeScale;

    // Set rotation to identity (or zero) from global constant
    localRot[0] = g_identityQuat[0]; // local_30
    localRot[1] = g_identityQuat[1]; // local_2c
    localRot[2] = g_identityQuat[2]; // local_28
    localRot[3] = g_identityQuat[3]; // local_24

    // Prepare output position (scaled) and rotation
    float outPos[3] = { localPos[0], localPos[1], localPos[2] }; // local_20, local_1c, local_18
    float outRot[4] = { localRot[0], localRot[1], localRot[2], localRot[3] }; // local_30 etc

    // Set the target transform on this entity
    // Parameters: this, pointer to target storage (this+0x184), position, rotation, time object, mode=3
    FUN_00850e80(this, (int*)(this + 0x184), &outPos[0], &outRot[0], currentTime, 3);
}