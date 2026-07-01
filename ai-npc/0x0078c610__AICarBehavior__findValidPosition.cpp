// FUNC_NAME: AICarBehavior::findValidPosition
// Address: 0x0078c610
// Role: Attempts to find a valid random position for AI car movement, with state-based retry logic.

#include <cstdlib> // for rand()

// Forward declarations of external functions
float getTickCount(); // FUN_00471610
bool getRandomPoint(int obj, float a, float b, Vector3& outPoint); // FUN_0078c000
bool canReachPosition(int handle, float timeOffset, const Vector3& point, int flags); // FUN_009a76f0

// Global constants (from data section)
extern float kAttemptInterval;       // DAT_01205228
extern float kRandomThreshold;       // _DAT_00d5c458
extern float kRandomMultiplier;      // DAT_00e44590
extern float kTimeOffset;            // _DAT_00d69a64

class AICarBehavior {
public:
    // Offsets:
    // +0x10: int handle (some object ID or handle)
    // +0x14: float lastAttemptTime
    // +0x18: int attemptState (0 = none, 1 = first attempt, 2 = second attempt)
    int handle;          // +0x10
    float lastAttemptTime; // +0x14
    int attemptState;      // +0x18

    bool findValidPosition(int obj, float a, float b, Vector3& outPosition);
};

bool AICarBehavior::findValidPosition(int obj, float a, float b, Vector3& outPosition) {
    if (obj == 0) {
        return false;
    }

    float currentTime = getTickCount();

    // Check if we need to start a new attempt cycle
    if (attemptState == 0 || (lastAttemptTime <= kAttemptInterval && kAttemptInterval != lastAttemptTime)) {
        // Randomly choose between two attempt types
        int randomVal = rand();
        if ((float)randomVal * kRandomMultiplier <= kRandomThreshold) {
            attemptState = 1;
        } else {
            attemptState = 2;
        }
        lastAttemptTime = kAttemptInterval + kTimeOffset;
    }

    // Compute a candidate point
    Vector3 candidate;
    if (!getRandomPoint(obj, a, b, candidate)) {
        return false;
    }

    // Check if the point is reachable
    float timeOffset = getTickCount() + 0x30; // iVar1 + 0x30
    if (canReachPosition(handle, timeOffset, candidate, 0) == 0) {
        // Success: store the point
        outPosition = candidate;
        return true;
    }

    // Failed: toggle attempt state for next try
    if (attemptState == 2) {
        attemptState = 1;
    } else if (attemptState == 1) {
        attemptState = 2;
        return false; // Both attempts failed, give up
    }

    return false;
}