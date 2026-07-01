// FUNC_NAME: isWithinCone
// Address: 0x00884c90
// Role: Checks if the dot product of a global direction vector and an object's forward vector exceeds a threshold.
//       Used for cone/FOV checks (e.g., player detection).

#include <cstdint>

// Global static initialization flag
static bool s_initializedFlag = false;

// Pointer to a static array of 3 floats representing a direction vector (e.g., camera forward)
static float* s_directionVector = nullptr;

// Threshold for dot product comparison (set externally)
extern float s_dotThreshold; // _DAT_00e541f0

// Forward declaration: returns pointer to a structure with a vector at offsets 0x10 (x), 0x14 (y), 0x18 (z)
int getObjectTransform(); // FUN_00471610

bool isWithinCone(int param_1)
{
    // First-call initialization: set direction vector from static data
    if (!(s_initializedFlag & 1)) {
        s_initializedFlag |= 1;
        s_directionVector = (float*)&DAT_00d77000; // static float array
    }

    // If param_1 is zero, skip the check (e.g., no target)
    if (param_1 == 0) {
        return false;
    }

    int transformPtr = getObjectTransform();
    if (transformPtr == 0) {
        return false;
    }

    // Extract object's forward vector (or position) from transform
    float objX = *(float*)(transformPtr + 0x10);
    float objY = *(float*)(transformPtr + 0x14);
    float objZ = *(float*)(transformPtr + 0x18);

    // Compute dot product with the global direction vector
    float dot = s_directionVector[0] * objX + s_directionVector[1] * objY + s_directionVector[2] * objZ;

    // Return true if dot product exceeds threshold (object is within cone)
    return (s_dotThreshold < dot);
}