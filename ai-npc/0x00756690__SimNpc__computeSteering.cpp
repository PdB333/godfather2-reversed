// FUNC_NAME: SimNpc::computeSteering
#include <cstdlib>  // for rand()

// External global variables (tuning constants)
extern float DAT_00e448bc;  // offset added to steering vector y component
extern float DAT_00d5ee60;  // threshold for using random angle
extern float DAT_00e44590;  // scaling factor for random angle
extern float DAT_00d5c458;  // offset for random angle (center)
extern float DAT_00d64e7c;  // probability threshold for flag setting

// External functions
extern void* getSimManager();  // FUN_00471610 - returns pointer to a singleton with position data
extern float getSteeringAngle(int index);  // FUN_00756360 - returns angle or direction magnitude
extern void transformVector(const float2& in, const float2& ref, float2& out1, float2& out2);  // FUN_00756460
extern int compareAndSelectVector(const float2& base, const float2& v1, const float2& v2);  // FUN_007565f0 - returns 0,1,2

class SimNpc {
public:
    // Offsets within the class (known from decompilation)
    // +0x54: int targetIndex (some identifier, e.g., waypoint ID or enemy ID)
    // +0x5c: int steeringResult (direction result: -1 invalid, 0,1,2)
    // +0x60: float steeringTargetX (desired movement vector x)
    // +0x68: float steeringTargetY (desired movement vector y)
    // +0x6c: byte flags (bit0 = apply random perturbation)
    
    int targetIndex;          // +0x54
    int steeringResult;       // +0x5c
    float targetX;            // +0x60
    float targetY;            // +0x68
    byte flags;               // +0x6c

    void computeSteering();
};

void SimNpc::computeSteering() {
    // Early out if target index indicates no target or special sentinel (0x48 = 72)
    if (targetIndex == 0 || targetIndex == 0x48) {
        steeringResult = -1;  // invalid direction
        return;
    }

    // Get the global context (likely the player's position/orientation source)
    void* simMgr = getSimManager();
    
    // Read a 2D vector from the singleton (likely current forward direction or position)
    // The data at +0x30: packed as two floats (x then y) in a 64-bit value?
    float2 currentForward = *(float2*)((char*)simMgr + 0x30);  // assume float2 layout: x low, y high
    float currentZ = *(float*)((char*)simMgr + 0x38);  // some third component (rotation, z, etc.)

    // Add a constant to the y component (maybe transform to world space)
    float2 baseVector = currentForward;
    baseVector.y += DAT_00e448bc;

    // Determine the actual index (subtract sentinel 0x48)
    int adjustedIndex = targetIndex - 0x48;  // since 0 and 0x48 are already excluded

    // Get a steering angle or magnitude based on the index
    float rawSteering = getSteeringAngle(adjustedIndex);

    float effectiveSteering;
    // If the steering value is very small, randomize it
    if (fabsf(rawSteering) <= DAT_00d5ee60) {
        effectiveSteering = (float)rand() * DAT_00e44590 - DAT_00d5c458;
    } else {
        effectiveSteering = rawSteering;
    }

    // Determine sign of the effective steering (positive => forward, negative => backward?)
    uint directionSign = (effectiveSteering > 0.0f) ? 1 : 0;

    // Compute local vectors relative to the base direction
    float2 transformed1, transformed2;
    transformVector(baseVector, currentForward, transformed1, transformed2);

    // If direction sign is 0 (negative steering), swap the computed vectors
    if (directionSign == 0) {
        transformed2 = transformed1;
        // Note: original code also sets local_1c = local_10 (which is the high part of transformed2's 64-bit? but simplified)
    }

    // Decide final target based on comparison of vectors
    int compareResult = compareAndSelectVector(baseVector, transformed1, transformed2);

    float2 finalTarget;
    int resultDirection;

    if (compareResult == 0) {
        // Straight path
        if ((float)rand() * DAT_00e44590 <= DAT_00d64e7c) {
            flags |= 1;   // flag bit 0: apply perturbation
        }
        resultDirection = (int)directionSign;
        finalTarget = transformed2;  // store the vector as target
    } else if (compareResult == 1) {
        // Slight deviation? Need to decide.
        if ((float)rand() * DAT_00e44590 <= DAT_00d64e7c) {
            flags |= 1;
            // Flip direction based on sign
            if (directionSign == 0) {
                resultDirection = -1;  // left/right
            } else if (directionSign == 1) {
                resultDirection = 0;
            } else {
                resultDirection = (directionSign == 0) ? 3 : -1;  // unclear
            }
            finalTarget = transformed1;
        } else {
            finalTarget = baseVector;
            resultDirection = 2;
        }
    } else if (compareResult == 2) {
        // Full deviation?
        if ((float)rand() * DAT_00e44590 <= DAT_00d64e7c) {
            flags |= 1;
        }
        resultDirection = (int)directionSign;
        finalTarget = transformed2;
    } else {
        // For any other result (though not expected)
        return;
    }

    // Store results
    steeringResult = resultDirection;
    targetX = finalTarget.x;
    targetY = finalTarget.y;
}