// FUNC_NAME: ChaseCamera::updateSmooth

// 0x006db660 - Camera smooth update with spring physics and state machine
// Updates output matrix based on input, smoothed using spring dynamics and blending over time

#include <cmath>

// External global flags (likely defined elsewhere)
extern bool gEnableCameraSmoothing;  // DAT_0112a8f8
extern float gFloatOne;             // _DAT_00d5780c (value ~1.0f)
extern float gMaxSpringDistance;    // DAT_00d58cbc (clamp for velocity)
extern float gEpsilon;              // DAT_00d5f2b4 (epsilon for zero check)

// Forward declarations of helper functions (defined elsewhere)
void springUpdate(float dt);
// FUN_0056b8a0: Convert 3x3 rotation (rows 8,9,10) to quaternion
void rotationToQuat(const float* mat, float* quat);
// FUN_006daac0: Apply spring velocity to a position based on dt
void applySpringToPosition(float* pos, float dt);
// FUN_0056c6b0: Compute angular delta between two vectors? (e.g., cross product)
void computeAngularDelta(const float* a, const float* b, float* out);
// FUN_0056c180: Convert quaternion to euler angles (pitch, yaw, roll)
void quatToEuler(const float* quat, float* euler);
// FUN_004a2210: Simple step easing (clamped t)
float easeStep(float t, int mode);
// FUN_004a2c80: Slerp between two quaternions with factor t, storing result in output
void quatSlerp(float* out, float t, const float* start, const float* end);

void __thiscall ChaseCamera::updateSmooth(float dt, const float* inputMatrix, float* outputMatrix)
{
    int state = *(int*)(this + 0x1a4);
    float elapsed = *(float*)(this + 0x1b0);
    float duration = *(float*)(this + 0x1ac);

    // If smoothing disabled, just copy input to output
    if (!gEnableCameraSmoothing)
    {
        for (int i = 0; i < 16; i++)
            outputMatrix[i] = inputMatrix[i];
        return;
    }

    // State machine: 2 or 3 means transition in progress
    if ((state == 2 || state == 3) && 
        (elapsed += dt, *(float*)(this + 0x1b0) = elapsed, (duration - elapsed) < 0.0f))
    {
        if (state == 2)
        {
            *(int*)(this + 0x1a4) = 0;      // idle
            *(char*)(this + 0x8) = 1;       // mark update needed
            return;
        }
        *(int*)(this + 0x1a4) = 1;          // to starting state
    }

    springUpdate(dt);  // Update internal spring dynamics

    // Get quaternion from input matrix's rotation part (rows 8,9,10)
    float inputQuat[4];
    rotationToQuat(inputMatrix + 8, inputQuat);

    // Spring velocities from fields
    float velX = *(float*)(this + 0x6c);  // maybe angular velocity
    float velPos = *(float*)(this + 0x60); // linear velocity

    // Predicted positions with velocity
    float targetPosA[3] = {
        inputMatrix[0] + velX * local_40,
        inputMatrix[1] + velX * fStack_3c,
        inputMatrix[2] + velX * fStack_38
    };
    float targetPosB[3] = {
        inputMatrix[0] + velPos * local_30,
        inputMatrix[1] + velPos * fStack_2c,
        inputMatrix[2] + velPos * fStack_28
    };

    // If parent object exists, compute relative offset
    int parentPtr = *(int*)(this + 0xe8);
    if (parentPtr != 0 && parentPtr != 0x48)
    {
        int parentBase;
        if (parentPtr == 0)
            parentBase = 0;
        else
            parentBase = parentPtr - 0x48;  // pointer arithmetic
        // Virtual call to get parent transform (offset 0xa4)
        (**(code**)(*(int*)parentBase + 0xa4))(&parentMatrix, this + 0xf0);
        // Store previous target
        float prevX = parentMatrix[0];
        float prevY = parentMatrix[4];
        float prevZ = parentMatrix[8];
        float prevW = gFloatOne;
        // Compute displacement to current target
        float diffX = parentMatrix[0] - *(float*)(this + 0x190);
        float diffY = parentMatrix[1] - *(float*)(this + 0x194);
        float diffZ = parentMatrix[2] - *(float*)(this + 0x198);
        float dist = sqrtf(diffX*diffX + diffY*diffY + diffZ*diffZ);
        if (gMaxSpringDistance < dist)
        {
            float scale = gMaxSpringDistance / dist;
            diffX *= scale;
            diffY *= scale;
            diffZ *= scale;
        }
        // If not snapping, add velocity to predicted positions
        if (*(char*)(this + 0x1a0) == 0)
        {
            float springCoeff = *(float*)(this + 0x70);
            targetPosB[0] += springCoeff * diffX;
            targetPosB[1] += springCoeff * diffY;
            targetPosB[2] += springCoeff * diffZ;
        }
        // Store current target for next frame
        *(float*)(this + 0x190) = prevX;
        *(float*)(this + 0x194) = prevY;
        *(float*)(this + 0x198) = prevZ;
        *(float*)(this + 0x19c) = prevW;
    }

    // Save input matrix as baseline (used for spring target)
    float springTarget[16];
    memcpy(springTarget, inputMatrix, 16 * sizeof(float));

    // Apply spring to positions if not snapping
    if (*(char*)(this + 0x1a0) == 0)
    {
        applySpringToPosition(targetPosA, dt);
        applySpringToPosition(springTarget, dt);
        applySpringToPosition(targetPosB, dt);
    }
    else
    {
        // Store matrices for snap (immediate)
        memcpy((float*)(this + 0x110), springTarget, 4 * sizeof(float));   // orientation
        memcpy((float*)(this + 0x170), targetPosA, 4 * sizeof(float));    // position A
        memcpy((float*)(this + 0x140), targetPosB, 4 * sizeof(float));    // position B
        *(char*)(this + 0x1a0) = 0;   // clear snap flag
    }

    // Compute differences from spring target
    float diffPosA[3] = { targetPosA[0] - springTarget[0],
                          targetPosA[1] - springTarget[1],
                          targetPosA[2] - springTarget[2] };
    float diffPosB[3] = { targetPosB[0] - springTarget[0],
                          targetPosB[1] - springTarget[1],
                          targetPosB[2] - springTarget[2] };

    // Normalize direction vectors
    float len = sqrtf(diffPosA[0]*diffPosA[0] + diffPosA[1]*diffPosA[1] + diffPosA[2]*diffPosA[2]);
    if (len > gEpsilon)
    {
        float invLen = gFloatOne / len;
        diffPosA[0] *= invLen;
        diffPosA[1] *= invLen;
        diffPosA[2] *= invLen;
    }
    else
    {
        diffPosA[0] = 0.0f;
        diffPosA[1] = 0.0f;
        diffPosA[2] = 0.0f;
    }

    len = sqrtf(diffPosB[0]*diffPosB[0] + diffPosB[1]*diffPosB[1] + diffPosB[2]*diffPosB[2]);
    if (len > gEpsilon)
    {
        float invLen = gFloatOne / len;
        diffPosB[0] *= invLen;
        diffPosB[1] *= invLen;
        diffPosB[2] *= invLen;
    }
    else
    {
        diffPosB[0] = 0.0f;
        diffPosB[1] = 0.0f;
        diffPosB[2] = 0.0f;
    }

    // Compute angular delta between the two direction vectors
    float angularDelta[3];
    computeAngularDelta(diffPosA, diffPosB, angularDelta);

    // Convert angular delta to euler angles (for orientation adjustment)
    float eulerDelta[3];
    quatToEuler(angularDelta, eulerDelta);

    // If state is 1 (starting transition), just output the spring target directly
    if (*(int*)(this + 0x1a4) == 1)
    {
        memcpy(outputMatrix, springTarget, 16 * sizeof(float));
        return;
    }

    // Compute blend factor using easing function
    float blend = easeStep(elapsed / duration, 1);   // simple step
    if (*(int*)(this + 0x1a4) == 3)
        blend = gFloatOne - blend;

    // Slerp the quaternion from stored start to target
    float* startQuat = (float*)(this + 0x110);  // stored start orientation
    quatSlerp(outputMatrix + 8, blend, startQuat, inputQuat);

    // Linearly interpolate position with blend factor
    float x0 = inputMatrix[0];
    float y0 = inputMatrix[1];
    float z0 = inputMatrix[2];
    float w0 = inputMatrix[3];
    float springW = springTarget[3];
    outputMatrix[0] = (x0 - springTarget[0]) * blend + springTarget[0];
    outputMatrix[1] = (y0 - springTarget[1]) * blend + springTarget[1];
    outputMatrix[2] = (z0 - springTarget[2]) * blend + springTarget[2];
    outputMatrix[3] = w0; // keep original w? (float4)
    // Note: The last line preserved w from input, not blended.
}