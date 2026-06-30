// FUNC_NAME: ChaseCamera::updateOrientation

// Address: 0x005fef10
// Role: Smooths yaw and pitch angles toward targets, then integrates angular velocity into orientation.
// The class is a chase camera controller used in EA EARS engine (The Godfather 2).
// Fields are accessed via float* this; offsets in comments are in bytes / 4.

#include <cstdint>

// Global constants (from .data section)
extern float DAT_00e44588; // minEpsilon? (≈0.001)
extern float DAT_00e2cd54; // smoothingScale? (≈1.0)
extern float DAT_00e2afac; // maxEpsilon? (≈0.5)
extern float DAT_00e2a848; // stepSize? (≈0.01)
extern uint32_t DAT_00e44680; // bitmask for delta time (e.g., 0xFFFFF)
extern float DAT_00e2b04c; // yawRateFactor? (≈0.5)

void __thiscall ChaseCamera::updateOrientation(float* this, float dt)
{
    // Guard: if inactive, skip
    if (this[0x38] == 0.0f) // +0xE0: isActive float
        return;

    // Compute yaw/pitch inputs if yawRate != 0
    if (this[0x43] != 0.0f) // +0x10C: yawRate
    {
        this[0x44] = (this[0x3B] - (float)((uint32_t)dt & DAT_00e44680)) // +0xEC: deltaTime
                   * this[0x3C]  // +0xF0: speed (smoothing factor)
                   * this[0x43]  // yawRate
                   * DAT_00e2b04c;
    }

    float fVar3 = DAT_00e44588;
    float fVar2 = DAT_00e2cd54;
    float fVar6 = DAT_00e2afac;
    float fVar1 = DAT_00e2a848;

    // Yaw smoothing (target - current)
    float yawDiff = this[0x3F] - this[0x3D]; // +0xFC: targetYaw, +0xF4: currentYaw
    if ((yawDiff != 0.0f) && (((uint32_t)this[0x2D] >> 6 & 1) == 0)) // +0xB4: flags
    {
        if (yawDiff <= fVar6) {
            if (yawDiff < fVar3) {
                yawDiff = yawDiff + fVar1;
            }
        } else {
            yawDiff = yawDiff - fVar1;
        }

        float smoothedYaw = this[0x3C] * yawDiff * fVar2
                          * (this[0x3B] + dt) + this[0x3D];
        this[0x3E] = smoothedYaw; // +0xF8: smoothedYaw

        // Clamp smoothed yaw
        if (smoothedYaw <= fVar6) {
            if (fVar3 <= smoothedYaw)
                goto LAB_005ff016;
            smoothedYaw = smoothedYaw + fVar1;
        } else {
            smoothedYaw = smoothedYaw - fVar1;
        }
        this[0x3E] = smoothedYaw;
    }
LAB_005ff016:

    // Pitch smoothing (target - current)
    if (((uint32_t)this[0x2D] >> 5 & 1) == 0) // check bit5 of flags
    {
        float pitchCurrent = this[0x40]; // +0x100: currentPitch
        float pitchTarget = this[0x42]; // +0x108: targetPitch
        if (pitchTarget != pitchCurrent)
        {
            float pitchDiff = pitchTarget - pitchCurrent;
            if (pitchDiff <= fVar6) {
                if (pitchDiff < fVar3) {
                    pitchDiff = pitchDiff + fVar1;
                }
            } else {
                pitchDiff = pitchDiff - fVar1;
            }

            float smoothedPitch = pitchDiff * (this[0x3B] + dt) * fVar2 * this[0x3C] + pitchCurrent;
            this[0x41] = smoothedPitch; // +0x104: smoothedPitch

            // Clamp smoothed pitch
            if (smoothedPitch <= fVar6) {
                if (fVar3 <= smoothedPitch)
                    goto LAB_005ff099;
                smoothedPitch = smoothedPitch + fVar1;
            } else {
                smoothedPitch = smoothedPitch - fVar1;
            }
            this[0x41] = smoothedPitch;
        }
    }
LAB_005ff099:

    // Update orientation (quaternion or axis‑angle) using angular velocity
    float fVar1_orig = this[3]; // save original w component (or angle)
    float fVar6 = (this[0x3B] - (float)((uint32_t)dt & DAT_00e44680)) * this[0x3C];
    fVar6 = fVar6 * fVar6; // squared time scale

    // Integrate orientation components
    this[0] = fVar6 * this[0x34] + this[0]; // +0x00: orientation.x
    this[1] = fVar6 * this[0x35] + this[1]; // orientation.y
    this[2] = fVar6 * this[0x36] + this[2]; // orientation.z
    this[3] = fVar6 * this[0x37] + this[3]; // +0x0C: orientation.w (if quaternion)

    // Restore original w component – only x,y,z updated (e.g., axis‑angle rotation)
    this[3] = fVar1_orig;
}