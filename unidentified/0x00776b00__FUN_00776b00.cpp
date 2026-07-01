// FUNC_NAME: SomeClass::checkRotationToTarget
// Function address: 0x00776b00
// Role: Checks if the object can rotate to face a target based on angle difference and rotation speed.

#include <cstdint>

// Forward declarations of helper functions (assumed from game code)
extern float __fastcall normalizeAngle(float angle); // FUN_00776440
extern bool __fastcall isRotationEnabled(int component); // FUN_008754e0
extern bool __fastcall isRotationDisabled(int component); // FUN_008754b0
extern void* __fastcall getTransform(); // FUN_00471610
extern void __fastcall setupFloatingPoint(); // FUN_00b9a9fa

// External float constants (from data section)
extern float const ANGLE_360;       // DAT_00d5d70c
extern float const ANGLE_0;         // DAT_00d5eeec
extern float const ROTATION_SPEED_FACTOR; // DAT_00d5efb8
extern float const ANGLE_NEGATIVE_OFFSET; // DAT_00e44578 (likely 360.0f)

class SomeClass {
public:
    // Offsets:
    // +0x5c: pointer to some state manager (e.g., GameStateManager)
    // +0x70: pointer to a component with vtable (e.g., RotationComponent)
    // +0x80: rotation enable/disable component
    // +0x88: some transform or target data
    // +0x90: computed target angle
    // +0xa0: max rotation speed (degrees per second)

    int checkRotationToTarget(int param_2); // param_2: time delta in milliseconds? (used as float)
};

int SomeClass::checkRotationToTarget(int param_2) {
    // Get state from manager at +0x5c
    int* managerPtr = *(int**)(this + 0x5c);
    if (managerPtr == nullptr) return 0;

    int state = *(int*)(managerPtr + 0x24c4); // Some state ID
    if (state == 0 || state == 0x48) {
        return 0;
    }

    // Check if rotation is enabled
    if (!isRotationEnabled(this + 0x80)) {
        return 0;
    }

    // Get two transforms and compute yaw difference
    void* transformA = getTransform();
    void* transformB = getTransform();
    float yawA = *(float*)(transformA + 0x30); // Yaw component
    float yawB = *(float*)(transformB + 0x30);
    float yawDiff = yawB - yawA;

    setupFloatingPoint();
    float normalizedDiff = normalizeAngle(yawDiff);
    *(float*)(this + 0x90) = normalizedDiff;

    // Get another transform and copy its orientation (16 floats = 64 bytes? Actually 8 undefined4 = 32 bytes)
    void* transformC = getTransform();
    float orientationData[8]; // 32 bytes
    for (int i = 0; i < 8; i++) {
        orientationData[i] = *(float*)(transformC + i * 4);
    }
    float targetYaw = orientationData[6]; // local_30 is the 7th float (index 6)

    setupFloatingPoint();
    float angleToTarget = normalizeAngle(normalizedDiff - targetYaw + ANGLE_0);
    if (angleToTarget < 0.0f) {
        angleToTarget += ANGLE_360;
    }

    // Determine direction of rotation
    bool isReversed = isRotationDisabled(this + 0x80);
    bool withinThreshold;
    if (!isReversed) {
        withinThreshold = (angleToTarget < ANGLE_0);
    } else {
        withinThreshold = (ANGLE_0 < angleToTarget);
    }

    if (!withinThreshold && ANGLE_0 != angleToTarget) {
        float timeDelta = (float)param_2;
        if (param_2 < 0) {
            timeDelta += ANGLE_NEGATIVE_OFFSET; // Normalize negative time? Unusual.
        }

        // Check if rotation speed is sufficient
        float maxRotation = *(float*)(this + 0xa0);
        if (maxRotation <= timeDelta * ROTATION_SPEED_FACTOR) {
            int* componentPtr = *(int**)(this + 0x70);
            if (componentPtr != nullptr && componentPtr != (int*)0x48) {
                int* vtableBase;
                if (componentPtr == 0) {
                    vtableBase = nullptr;
                } else {
                    vtableBase = (int*)(componentPtr - 0x48); // Adjust pointer to get vtable
                }
                // Call virtual function at index 125 (offset 500)
                int (__thiscall* vfunc)(void*) = (int (__thiscall*)(void*))(*(int*)(*vtableBase + 500));
                if (vfunc(this + 0x88) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}