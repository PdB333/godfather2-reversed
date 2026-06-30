// FUNC_NAME: ChaseCamera::updateSmoothMove
// Address: 0x006d9f60
// This function updates a smooth chase camera or vehicle camera interpolation
// It computes a damped position towards a target using velocity and acceleration parameters
// param_1: this pointer to camera object
// param_2: deltaTime (frame time)
// param_3: unused? (might be flags)
// param_4: output 4x3 matrix? (position and orientation floats, 12 floats)

#include <cmath>

// Global constants from decompilation
extern float g_smoothMaxSpeed;          // _DAT_00d5780c
extern uint32_t g_rotationIndexMask;    // DAT_010c2678 (bitmask)
extern int32_t g_rotationIndex;         // DAT_012054b4 (counter)
extern float g_rotationFactor;          // DAT_00d5eee4 (multiplier)
extern int32_t g_comparisonValue;       // DAT_0112a8f4 (type check)
extern float g_gravityFactor;           // _DAT_00d5f5bc (used in final blend)
extern float g_smallEpsilon;            // from PTR_FUN_00e4462c (used as additive)

// Forward declarations of helper functions (from Ghidra)
void matrixFromBasisVectors(float *outBasis, float *inVector, float *position); // FUN_0056b8a0
void rotateVectorTranspose(float *vec, float *rot, float *out);                // FUN_0056de00
void integrateVerlet(float *pos, float *vel, float *acc, float *dummy);        // FUN_00473bc0

void __thiscall ChaseCamera::updateSmoothMove(void *thisObj, float deltaTime, undefined4 param_3, float *outputMatrix)
{
    float *speedTimer = (float *)((char *)thisObj + 0x54); // Timer for interpolation speed
    float targetX, targetY, targetZ, targetW;               // Interpolated target position?
    float velocityX, velocityY, velocityZ, velocityW;       // Derived velocity
    float resultX[3], resultY[3], resultZ[3];               // Temporary arrays
    float blendFactor;
    float *clampPtr;

    // Initialize local arrays to zero
    float local80 = 0.0f, local7c = 0.0f, local78 = 0.0f, local74 = 0.0f;
    float local60 = 0.0f, local5c = 0.0f, local58 = 0.0f, local54 = 0.0f;

    float currentSpeed = g_smoothMaxSpeed;
    if (g_smoothMaxSpeed <= *speedTimer)
    {
        // Generate a pseudo-random rotation using global index
        uint32_t idx = DAT_010c2678 & (uint32_t)g_rotationIndex;
        uint32_t idx1 = (uint32_t)g_rotationIndex + 1;
        uint32_t idx2 = (uint32_t)g_rotationIndex + 2;

        float targetTime = *(float *)((char *)thisObj + 0x28); // Unknown: maybe target speed or time
        float frameFactor = *(float *)(&g_rotationFactorTable + (DAT_010c2678 & ((uint32_t)g_rotationIndex + 3)) * 4);
        float rawRotation = frameFactor * g_rotationFactor - g_smoothMaxSpeed;

        // Compute offset using rotation and object's orientation components
        float rotX = *(float *)((char *)thisObj + 0x30);
        float rotY = *(float *)((char *)thisObj + 0x34);
        float rotZ = *(float *)((char *)thisObj + 0x38);

        float rotation0 = *(float *)(&g_rotationFactorTable + idx * 4) * g_rotationFactor - g_smoothMaxSpeed;
        float rotation1 = *(float *)(&g_rotationFactorTable + (DAT_010c2678 & idx1) * 4) * g_rotationFactor - g_smoothMaxSpeed;
        float rotation2 = *(float *)(&g_rotationFactorTable + (DAT_010c2678 & idx2) * 4) * g_rotationFactor - g_smoothMaxSpeed;

        // Combine to get target velocity
        velocityX = rawRotation * rotX + targetTime * rotation0;
        velocityY = rawRotation * rotY + targetTime * rotation1;
        velocityZ = rawRotation * rotZ + targetTime * rotation2;

        // VelocityW is not computed here (remains 0.0)

        // If object's type matches specific value, adjust rotation
        int32_t typeFlag = *(int32_t *)((char *)thisObj + 0x40);
        if (typeFlag == g_comparisonValue)
        {
            // Convert output matrix vectors for rotation and apply transpose
            FUN_0056b8a0(outputMatrix[9], outputMatrix[8], outputMatrix[10], (undefined (*) [32])local50);
            FUN_0056de00(&velocityX, local30, &velocityX);
        }

        // Store the computed velocity as target
        *(float *)((char *)thisObj + 0x70) = velocityX;
        *(float *)((char *)thisObj + 0x74) = velocityY;
        *(float *)((char *)thisObj + 0x78) = velocityZ;
        *(float *)((char *)thisObj + 0x7c) = 0.0f; // velocityW

        // Compute delta between target and current position
        float diffX = *(float *)((char *)thisObj + 0x70) - *(float *)((char *)thisObj + 0x60);
        float diffY = *(float *)((char *)thisObj + 0x74) - *(float *)((char *)thisObj + 0x64);
        float diffZ = *(float *)((char *)thisObj + 0x78) - *(float *)((char *)thisObj + 0x68);
        float diffW = *(float *)((char *)thisObj + 0x7c) - *(float *)((char *)thisObj + 0x6c);

        // Compute acceleration magnitude (inverse of distance + epsilon)
        float dist = sqrt(diffX*diffX + diffY*diffY + diffZ*diffZ) + g_smallEpsilon;
        float acceleration = *(float *)((char *)thisObj + 0x20) / dist; // +0x20 likely damping
        *(float *)((char *)thisObj + 0x58) = acceleration;

        // Reset speed timer to 0
        *speedTimer = 0.0f;
    }

    // Update speed timer: accelerate
    float speed = *(float *)((char *)thisObj + 0x58) * deltaTime + *speedTimer;
    *speedTimer = speed;

    // Clamp speed between 0 and maxSpeed
    if (speed <= g_smoothMaxSpeed)
    {
        if (speed >= 0.0f)
            clampPtr = speedTimer;  // Use current speed
        else
            clampPtr = &local84;    // Zero (local84 initialized 0)
    }
    else
    {
        clampPtr = &g_smoothMaxSpeed; // Clamp to max
    }
    float clampedSpeed = *clampPtr;
    *speedTimer = clampedSpeed;

    // Blend current position toward target using clampedSpeed
    float blendWeight = *(float *)((char *)thisObj + 0x50); // Varies over time
    float currentX = *(float *)((char *)thisObj + 0x60);
    float currentY = *(float *)((char *)thisObj + 0x64);
    float currentZ = *(float *)((char *)thisObj + 0x68);
    float currentW = *(float *)((char *)thisObj + 0x6c);

    float targetX = *(float *)((char *)thisObj + 0x70);
    float targetY = *(float *)((char *)thisObj + 0x74);
    float targetZ = *(float *)((char *)thisObj + 0x78);
    float targetW = *(float *)((char *)thisObj + 0x7c);

    // Interpolate: newPos = (target - current) * clampedSpeed + current
    float newX = g_gravityFactor * 0.0f + blendWeight * ((targetX - currentX) * clampedSpeed + currentX);
    float newY = g_gravityFactor * 0.0f + blendWeight * ((targetY - currentY) * clampedSpeed + currentY);
    float newZ = g_gravityFactor * g_smoothMaxSpeed + blendWeight * ((targetZ - currentZ) * clampedSpeed + currentZ);
    float newW = 0.0f; // Not interpolated

    // Initialize local vectors for Verlet integration
    float velX = 0.0f, velY = 0.0f, velZ = 0.0f, velW = 0.0f;
    float accX = 0.0f, accY = 0.0f, accZ = 0.0f;

    // Call Verlet-like integration with position and zero acceleration?
    FUN_00473bc0(&currentX, &newX, 0, &velX, &currentY, &velY); // Function signature may differ

    // Decrease blend weight over time based on deltaTime vs a threshold
    if (0.0f < *(float *)((char *)thisObj + 0x2c))
    {
        float weightReduction = *(float *)((char *)thisObj + 0x50)
                                - (deltaTime / *(float *)((char *)thisObj + 0x2c)) * *(float *)((char *)thisObj + 0x24);
        *(float *)((char *)thisObj + 0x50) = weightReduction;
        if (weightReduction <= 0.0f)
        {
            *(float *)((char *)thisObj + 0x50) = 0.0f;
            *(uint8_t *)((char *)thisObj + 8) = 1; // Mark as completed or something
        }
    }

    // Apply computed offset to output matrix (position and orientation?)
    outputMatrix[0] += currentX;
    outputMatrix[1] += currentY;
    outputMatrix[2] += currentZ;
    outputMatrix[3] = outputMatrix[3]; // W component (unchanged)

    outputMatrix[8] += currentX; // Different position? Possibly two sets (position and look-at)
    outputMatrix[9] += currentY;
    outputMatrix[10] += currentZ;
    outputMatrix[11] = outputMatrix[11]; // Second W unchanged
}