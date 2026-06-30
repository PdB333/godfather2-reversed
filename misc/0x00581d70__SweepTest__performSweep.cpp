// FUNC_NAME: SweepTest::performSweep
// Function address: 0x00581d70
// Role: Performs a swept collision test (raycast or shape sweep) against a target object.
// Uses a virtual function at vtable+0xc on the hit object to compute intersection.
// Returns true if a hit occurred, false otherwise.

#include <cstdint>

// Forward declarations
struct Vector4 {
    float x, y, z, w;
};

struct SweepResult {
    void* hitObject;      // +0x00
    float minDist;        // +0x04
    float maxDist;        // +0x08
    float pad0;           // +0x0c (unused)
    Vector4 hitPoint;     // +0x10
    Vector4 hitNormal;    // +0x20
};

// Global constant (likely FLT_MAX or similar)
extern const float g_sweepInfinity = *(float*)0x00e2b1a4;

// External functions
uint32_t getCollisionFilterFlags(); // FUN_00571070
void someCleanupFunction();         // FUN_0056fb60

class SweepTest {
public:
    // Vtable at offset 0
    // Fields (offsets relative to this):
    // +0x04: uint32_t flags
    // +0x1c: float field7 (saved/restored during sweep)
    // +0x20: float field8 (saved/restored)
    // +0x24: float field9 (sweep length or speed)
    // ... other fields

    bool performSweep(SweepResult* result) {
        // Initialize result vectors to zero with w = infinity
        result->hitPoint = {0.0f, 0.0f, 0.0f, g_sweepInfinity};
        result->hitNormal = {0.0f, 0.0f, 0.0f, g_sweepInfinity};

        float minDist = result->minDist;
        float maxDist = result->maxDist;
        float adjustedMax = this->field9 - g_sweepInfinity; // param_1[9] - global

        if (minDist < adjustedMax) {
            float newMax = maxDist;
            if (adjustedMax <= maxDist) {
                newMax = adjustedMax;
            }
            if (minDist < newMax) {
                uint32_t flags = getCollisionFilterFlags();
                if (this == result->hitObject) {
                    flags &= ~0x10; // Ignore self
                } else {
                    flags |= 0x10;  // Include other objects
                }

                // Save state
                uint32_t savedFlags = this->flags;       // param_1[4]
                float savedField7 = this->field7;        // param_1[7]
                float savedField8 = this->field8;        // param_1[8]

                // Set temporary state
                this->flags |= 0x801000;
                this->field8 = minDist;
                this->field7 = newMax;

                // Virtual call on hitObject (vtable+0xc = index 3)
                typedef int* (__thiscall *HitFunc)(void*, uint32_t);
                HitFunc hitFunc = (HitFunc)(*(void***)result->hitObject)[3];
                int* hitData = hitFunc(result->hitObject, flags);

                if (hitData) {
                    // Copy hit point and normal from hitData
                    result->hitPoint.x = *(float*)(hitData + 4);  // +0x10
                    result->hitPoint.y = *(float*)(hitData + 5);  // +0x14
                    result->hitPoint.z = *(float*)(hitData + 6);  // +0x18
                    result->hitPoint.w = *(float*)(hitData + 7);  // +0x1c
                    result->hitNormal.x = *(float*)(hitData + 8); // +0x20
                    result->hitNormal.y = *(float*)(hitData + 9); // +0x24
                    result->hitNormal.z = *(float*)(hitData + 10);// +0x28
                    result->hitNormal.w = *(float*)(hitData + 11);// +0x2c
                }

                someCleanupFunction();

                // Restore state
                this->field7 = savedField7;
                this->flags = savedFlags;
                this->field8 = savedField8;

                return hitData != nullptr;
            }
        }
        return false;
    }

private:
    // Placeholder fields (actual layout unknown)
    uint32_t flags;       // +0x04
    // ... padding ...
    float field7;         // +0x1c
    float field8;         // +0x20
    float field9;         // +0x24
};