// FUNC_NAME: ChaseCamera::update
// Function at 0x005fea70: Updates the spring/damper physics for the chase camera.
// This is a __thiscall member function of ChaseCamera.
// It computes forces to make the camera follow a target position with spring-like behavior,
// including angular (yaw) velocity control, speed limits, and acceleration constraints.

#include <cmath>

const float g_invDistanceThreshold = 0.0f; // DAT_00e2cbe0 (likely 0)
const float g_velocityScale = 1.0f;        // DAT_00e2b1a4 (appears as 1/distance factor)
const float g_yawOffset = 0.0f;            // DAT_00e44564 (yaw error bias)
const float g_yawDeadZoneNeg = -0.01f;     // DAT_00e44588 (negative dead zone)
const float g_yawDeadZonePos = 0.01f;      // DAT_00e2afac (positive dead zone)
const float g_yawStep = 0.1f;              // DAT_00e2a848 (yaw increment step)
const float g_speedDamping = 0.9f;         // DAT_00e2cd54 (speed damp factor)
const float g_forceScale = 1.0f;           // DAT_00e35654 (scale for force calc)
const float g_invForceScale = 1.0f;        // DAT_00e44968 (inverse of something)

// Forward declarations for subcalls (addresses)
void initCameraTarget(void* thisPtr, void* a, int* b, int c); // FUN_005fe2e0
void clampRandom(); // FUN_00b9a9fa (probably does nothing or random)
bool checkSomething(void* ptr); // FUN_005f5d30 (check flag)

class ChaseCamera {
public:
    // Offsets: (relative to 'this')
    // +0x7c: unknown pointer (maybe target owner)
    // +0x88: boolean flag (nil check for currentPos)
    // +0x90: float* currentPos (3 floats: x,y,z)
    // +0x94: void* targetObject
    // +0x9c: float* targetPos (3 floats)
    // +0xb4: uint flags (bitfield)
    // +0x60: float restX (position offset for spring)
    // +0x68: float restZ (position offset)
    // +0xc0: float minSpeed
    // +0xc4: float maxSpeed
    // +0xd0: float forceX (spring result)
    // +0xd4: float forceY (yaw result)
    // +0xd8: float forceZ (spring result)
    // +0xe0: uint (cleared)
    // +0xe4: float accelLimit (positive)
    // +0xe8: float accelLimitNeg (negative yaw limit)
    // +0xec: float currentSpeed
    // +0xf0: float invSpeed (1/currentSpeed or 0)
    // +0xf4: float prevYawVelocity
    // +0xf8: float currentYawVelocity
    // +0xfc: float targetYawVelocity
    // +0x100: float desiredYaw
    // +0x104: float previousDesiredYaw
    // +0x108: float yawError (computed)
    // +0x10c: float yawAcceleration
    // +0x110: float yawAcceleration2

    void update(char applyForce) {
        float dx, dy, dz;
        float dxCurrent, dzCurrent;
        float distSq, dist;
        float speedFactor, speed, yawError;
        float maxSpeed, minSpeed;
        float yawDiff, accelLimit;
        float forceX, forceZ, forceYaw;
        float speedAlpha;
        uint flags;
        bool isInitialized;

        // Check if target pointers are valid; if not, initialize
        if (*(void**)(&this[0x94]) == 0 || *(void**)(&this[0x9c]) == 0) {
            initCameraTarget(this, (void*)(this + 0x88),
                             (int*)(this + 0x94),
                             *(uint*)(this + 0xb4) >> 0xd & 0xffffff01);
        }

        if (*(void**)(&this[0x94]) != 0) {
            float* targetPos = *(float**)(&this[0x9c]);
            if (targetPos != 0) {
                float* currentPos;
                if (*(int*)(&this[0x88]) == 0) {
                    currentPos = 0; // Warning: null dereference later? Maybe safe due to condition
                } else {
                    currentPos = *(float**)(&this[0x90]);
                }
                // Perform operations even if currentPos is null? Assume not null in practice.
                dx = targetPos[0] - currentPos[0];
                dy = targetPos[1] - currentPos[1];
                dz = targetPos[2] - currentPos[2];
                distSq = dy * dy + dx * dx + dz * dz;
                dist = 0.0f;
                speedFactor = 0.0f;
                if (g_invDistanceThreshold < distSq) {
                    dist = sqrt(distSq);
                    speedFactor = g_velocityScale / dist;
                }

                flags = *(uint*)(&this[0xb4]);
                // Condition: if bit7 is clear OR target is different from stored, OR target exists and position pointer differs
                if (((flags >> 7 & 1) == 0) ||
                    (*(void**)(&this[0x94]) != *(void**)(&this[0x7c])) ||
                    (*(void**)(&this[0x94]) != 0 &&
                     *(void**)(&this[0x9c]) != *(void**)(&this[0x84]))) {
                    // Reset yaw velocity if not locked (bit6)
                    if (*(float*)(&this[0xf8]) != *(float*)(&this[0xfc]) &&
                        ((flags >> 6 & 1) == 0)) {
                        *(float*)(&this[0xf8]) = *(float*)(&this[0xfc]);
                    }
                    // Compute yaw error from x component
                    float yawFromX = speedFactor * dx;
                    clampRandom(); // noise/clamp
                    *(float*)(&this[0xfc]) = yawFromX;
                }
                // Compute yaw error from y component
                float yawFromY = speedFactor * dy;
                clampRandom();
                yawError = g_yawOffset - yawFromY;
                *(float*)(&this[0x108]) = yawError;

                // Clear yaw accelerations if bit4 set
                if ((flags >> 4 & 1) != 0) {
                    *(uint*)(&this[0x110]) = 0;
                    *(uint*)(&this[0x10c]) = 0;
                }

                *(uint*)(&this[0xe0]) = 0;

                if (applyForce == 0) {
                    // No force mode: simply copy yaw velocities
                    if ((flags >> 5 & 1) == 0) {
                        *(float*)(&this[0x100]) = yawError;
                        *(float*)(&this[0x104]) = yawError;
                    }
                    if ((flags >> 6 & 1) == 0) {
                        goto LAB_SET_PREVIOUS;
                    }
                } else {
                    // Apply force mode
                    if ((flags >> 3 & 1) == 0) {
                        // Check if target changed (bit7) and something else allows override
                        if (((flags >> 7 & 1) != 0) && checkSomething(this + 0x7c)) {
                            *(float*)(&this[0x100]) = yawError;
                            *(float*)(&this[0x104]) = yawError;
                            goto LAB_SET_PREVIOUS;
                        }
                        // Check if yaw velocity needs update
                        if ((*(float*)(&this[0xfc]) != *(float*)(&this[0xf4])) ||
                            (((flags >> 5 & 1) == 0 && (yawError != *(float*)(&this[0x100]))))) {
                            maxSpeed = *(float*)(&this[0xc4]);
                            speed = dist;
                            if (maxSpeed <= dist) {
                                speed = maxSpeed;
                            }
                            if ((flags >> 9 & 1) == 0) {
                                speed = speed * g_speedDamping;
                            }
                            minSpeed = maxSpeed - *(float*)(&this[0xc0]);
                            if (minSpeed < speed) {
                                speed = minSpeed;
                            }
                            if (speed < 0.0f) {
                                speed = 0.0f;
                            }
                            // Compute yaw diff with dead zone
                            yawDiff = *(float*)(&this[0xf4]) - *(float*)(&this[0xfc]);
                            if (yawDiff <= g_yawDeadZonePos) {
                                if (yawDiff < g_yawDeadZoneNeg) {
                                    yawDiff = yawDiff + g_yawStep;
                                }
                            } else {
                                yawDiff = yawDiff - g_yawStep;
                            }
                            // Apply acceleration limit
                            accelLimit = *(float*)(&this[0xe4]);
                            if (0.0f < accelLimit) {
                                if (yawDiff < 0.0f) {
                                    accelLimit = *(float*)(&this[0xe8]);
                                }
                                if (accelLimit < speed) {
                                    speed = accelLimit;
                                }
                            }
                            *(float*)(&this[0xec]) = speed;
                            speedAlpha = (speed > 0.0f) ? (g_velocityScale / speed) : g_invForceScale;
                            *(float*)(&this[0xf0]) = speedAlpha;

                            // Compute angular acceleration if bit4 set and yaw velocity changing
                            if (((flags >> 4 & 1) != 0) &&
                                (*(float*)(&this[0xfc]) != *(float*)(&this[0xf4]))) {
                                *(float*)(&this[0x10c]) = yawDiff * g_forceScale;
                            }

                            // Compute spring forces based on current vs target position
                            float factor1 = (speed / maxSpeed) * g_forceScale;
                            float factor2 = factor1;
                            if (dist > 0.0f) {
                                factor2 = (speed / dist) * g_forceScale;
                            }
                            forceX = (dx) * factor2 - (currentPos[0] - *(float*)(&this[0x60])) * factor1;
                            forceZ = (dz) * factor2 - (currentPos[2] - *(float*)(&this[0x68])) * factor1;
                            *(float*)(&this[0xd0]) = forceX;
                            *(float*)(&this[0xd8]) = forceZ;

                            // Yaw force only if yaw target changed
                            if (((flags >> 5 & 1) == 0) && (yawError != *(float*)(&this[0x100]))) {
                                *(float*)(&this[0xd4]) = ( *(float*)(&this[0x100]) - yawError ) * speed * g_forceScale;
                                return; // Early return with yaw force set
                            }
                            *(uint*)(&this[0xd4]) = 0;
                        }
                    }
                }
                return;
            }
        }
        return;

    LAB_SET_PREVIOUS:
        // Copy current yaw velocity to previous
        *(float*)(&this[0xf4]) = *(float*)(&this[0xfc]);
        *(float*)(&this[0xf8]) = *(float*)(&this[0xfc]);
    }
};