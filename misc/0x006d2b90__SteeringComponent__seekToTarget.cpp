// FUNC_NAME: SteeringComponent::seekToTarget
// Address: 0x006d2b90
// Role: AI steering behavior - clamps velocity magnitude to maxSpeed, then computes error vector to target,
// checks for obstacles, adjusts velocity accordingly, and updates internal physics state.

#include <cmath>

// Global constant: minimum speed threshold (from _DAT_00d577a0)
extern const float kMinSpeedThreshold;

// Forward declarations of helper functions (likely in same module)
bool checkObstacle(const float* target, const float* delta, int param);
bool adjustForTerrainCollision(const float* delta, const float* target);

void __thiscall SteeringComponent::seekToTarget(int* this, float* targetPos, float maxSpeed, int deltaTime) {
    float* velocityPtr;
    float speedSq;
    float dx, dy, dz;
    float fVar3;
    float fVar2;
    float fVar5;
    bool bVar1;

    // Compute current velocity magnitude (from offsets +0x60..+0x6C)
    speedSq = sqrtf(
        (float)this[0x18] * (float)this[0x18] +
        (float)this[0x19] * (float)this[0x19] +
        (float)this[0x1A] * (float)this[0x1A]
    );

    // Clamp velocity if within [kMinSpeedThreshold, maxSpeed]
    if ((kMinSpeedThreshold < speedSq) && (speedSq < maxSpeed)) {
        float scale = maxSpeed / speedSq;
        this[0x22] = (int)maxSpeed;                 // +0x88: store clamped speed
        this[0x18] = (int)(scale * (float)this[0x18]); // +0x60
        this[0x19] = (int)(scale * (float)this[0x19]); // +0x64
        this[0x1A] = (int)(scale * (float)this[0x1A]); // +0x68
        this[0x1B] = (int)(scale * (float)this[0x1B]); // +0x6C (unused?)
    }

    // Compute error vector = targetPos - velocity (stored at this+4, offset +0x10)
    fVar5 = targetPos[1];
    fVar2 = targetPos[2];
    fVar3 = targetPos[3];
    velocityPtr = (float*)(this + 4);
    *velocityPtr = *targetPos - (float)this[0x18];
    this[5] = (int)(fVar5 - (float)this[0x19]);     // +0x14
    this[6] = (int)(fVar2 - (float)this[0x1A]);     // +0x18
    this[7] = (int)(fVar3 - (float)this[0x1B]);     // +0x1C

    // Check for obstacle using the error vector
    if (!checkObstacle(targetPos, velocityPtr, 0)) {
        bVar1 = adjustForTerrainCollision(velocityPtr, targetPos);
        if (bVar1) {
            // Adjust velocity to correct for terrain collision
            fVar5 = targetPos[1];
            fVar2 = targetPos[2];
            fVar3 = targetPos[3];
            this[0x18] = (int)(*targetPos - *velocityPtr);
            this[0x19] = (int)(fVar5 - (float)this[5]);
            this[0x1A] = (int)(fVar2 - (float)this[6]);
            this[0x1B] = (int)(fVar3 - (float)this[7]);
        }
    }

    // Call virtual update on subobject at offset +0x20 (this+8)
    (*(code**)(*(int*)this + 0x18))(this + 8, targetPos, deltaTime);
}