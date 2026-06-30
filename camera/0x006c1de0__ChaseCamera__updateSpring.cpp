// FUNC_NAME: ChaseCamera::updateSpring
// Function address: 0x006c1de0
// This function updates a spring-based camera smoothing system.
// It computes a smooth offset (output in param_2) based on input acceleration (param_5),
// damping (param_7), delta time (param_8), and internal state.
// The state is stored in the object pointed to by param_1 (this).

#include <math.h>

// Constants (inferred from globals)
constexpr float DEG_TO_RAD = 0.01745329252f; // example
constexpr float kIdentityQuatW = 1.0f; // DAT_00d5eea0 likely 1.0 (identity quaternion w)
constexpr float kQuatEpsilon = 0.0001f; // DAT_00d5efc8?

// External helper functions (declared elsewhere)
float getFrameTime(); // FUN_00471610
void syncTime(); // FUN_00b9a9fa
float clampAngle(float angle); // FUN_004a1580 (normalize angle to [0,2pi] or [-pi,pi])
void* getInputManager(); // FUN_007ff880 (returns pointer to input manager)
bool isKeyDown(int key); // FUN_0085e050 (check key press, e.g., key 0xE)
bool isGamePaused(); // FUN_00410eb0
void rotateVectorByQuaternion(float* outVec, const float* inVec, const float* quat, float angle); // FUN_004a0370 (likely quaternion rotation)
void integrateSpring(float* outPos, float dt); // FUN_006daac0 (integration of spring dynamics)
void updateSmoothing(float* state); // FUN_006c0810 (some smoothing update)
bool checkDebugHash(unsigned int hash); // FUN_0079e920 (hash check for debug features)
bool checkDebugFlag(); // FUN_00549a40 (get a debug boolean)

// Global states (used as singletons)
extern float g_springTimer; // DAT_0112a6e8
extern float g_springTimerPrev; // DAT_0112a6e4
extern float g_springDamping; // DAT_0112a6f0 (damping factor)
extern float g_springMin; // DAT_00e50e04? actually many constants
extern float g_springMax; // DAT_00e50e08

// Assumed structure of the spring state (offsets relative to this)
struct SpringState {
    // +0x00: struct header? (2 bytes? + floats)
    uint16_t magic; // DAT_00e50df6
    float currentValue; // +0x04 (output value)
    float unknownFloat; // +0x08 (DAT_00e50e28)
    // many other fields follow...
};

// Actual function reconstruction starts here
void __thiscall ChaseCamera::updateSpring(
    void* thisPtr,          // param_1
    float* outDirection,    // param_2 (output vector)
    float inputAccel,       // param_5 (acceleration input, e.g., stick magnitude)
    float springDamping,    // param_7 (damping factor)
    float deltaTime,        // param_8 (time step)
    int unused1,            // param_3 (unused)
    int unused2,            // param_4 (unused)
    float unused3           // param_6 (unused)
) {
    // Decode this pointer as byte pointer for offset arithmetic
    char* self = (char*)thisPtr;
    float* stateFloats = (float*)thisPtr;

    // Get current time from a global clock
    double rawTime = *(double*)(getFrameTime() + 0x20);
    syncTime();
    float deltaTimeFromClock = (float)(rawTime - *(double*)(getFrameTime() + 0x20));

    // Adjust deltaTime if a flag is set (offset 0x3a)
    if (self[0x3a] != 0) {
        deltaTimeFromClock = clampAngle(deltaTimeFromClock + *reinterpret_cast<float*>(0x00d5eeec));
    }

    // Input manager check
    bool forceAccel = false;
    void* inputMgr = getInputManager();
    if (inputMgr != nullptr) {
        if (self[0x3a] == 0 || isKeyDown(0x0E)) {
            forceAccel = false;
        } else {
            forceAccel = true;
            inputAccel = 0.0f;
        }
    }

    // Game pause check
    bool isPaused = isGamePaused() == 0;
    float noiseThreshold = *reinterpret_cast<float*>(0x00d5780c); // some threshold, maybe 0.001

    // Accumulate input acceleration into internal state (offset +0x34)
    stateFloats[0x34 / 4] += inputAccel;

    // Get a constant (maybe identity quaternion w)
    float identityW = *reinterpret_cast<float*>(0x00d5cf70);

    // Branch on active state flag at offset 0x30
    if (self[0x30] == 0) {
        // Not active
        if (!isPaused) {
            goto LAB_006c1f3f; // Jump to activate state
        }

        // ... (the original code goes to LAB_006c1ff1 after this check)
        // For readability, I'll follow the decompiled flow
        if (self[0x30] != 0) {
            // If active (should not happen here, but guard)
            updateSmoothing(nullptr); // dummy
            // ... skip to end
            goto LAB_006c26b1;
        }

        // Normal idle path
        float idleValue = *reinterpret_cast<float*>(0x00e50e10); // some idle constant
        if (inputAccel != 0.0f) {
            // Accelerating: increase internal speed
            float maxSpeed = noiseThreshold; // from constant
            float accelFactor = (springDamping / *reinterpret_cast<float*>(0x0112a6f0)) * deltaTime;
            if (accelFactor > maxSpeed) {
                accelFactor = maxSpeed;
            }
            float newSpeed = clampAngle(stateFloats[0x4c / 4] + accelFactor);
            stateFloats[0x4c / 4] = newSpeed;
            // Reset other state
            stateFloats[0x40 / 4] = 0.0f;
            stateFloats[0x44 / 4] = 0.0f;
            stateFloats[0x50 / 4] = 0.0f;
            stateFloats[0x54 / 4] = 0.0f;
            stateFloats[0x48 / 4] = identityW;
            // Apply rotation
            rotateVectorByQuaternion(&stateFloats[0x40 / 4], &stateFloats[0x40 / 4], nullptr, newSpeed);
            // Set timers
            stateFloats[0x58 / 4] = identityW; // some timer
            stateFloats[0x5c / 4] = 0.0f;
            self[0x38] = 1; // flag
            self[0x39] = 0;
            self[0x3c] = 0;
            stateFloats[0x60 / 4] = 0.0f;
            // Decay check
            if (0.0f <= stateFloats[0x68 / 4] * accelFactor) {
                stateFloats[0x70 / 4] = 0.0f;
            } else {
                stateFloats[0x70 / 4] += deltaTime;
                if (*reinterpret_cast<float*>(0x00e50e40) < stateFloats[0x70 / 4]) {
                    stateFloats[0x6c / 4] = 0.0f;
                    stateFloats[0x68 / 4] = 0.0f;
                }
            }
            stateFloats[0x6c / 4] += deltaTime;
            stateFloats[0x68 / 4] += accelFactor;
            // Update global timer
            g_springTimer -= deltaTime;
            if (g_springTimer < 0.0f) g_springTimer = 0.0f;
            goto LAB_006c26b1;
        }

        // No acceleration: deceleration phase
        float currentSpeed = stateFloats[0x4c / 4];
        float prevSpeed = stateFloats[0x50 / 4];
        // Apply damping
        float newSpeed = clampAngle(currentSpeed - deltaTimeFromClock);
        float newPrev = clampAngle(deltaTimeFromClock - prevSpeed);
        stateFloats[0x4c / 4] = newSpeed;
        stateFloats[0x50 / 4] = newPrev;

        // Increase global timer
        g_springTimer += deltaTime;
        if (g_springTimer > *reinterpret_cast<float*>(0x00e50e44)) {
            g_springTimer = *reinterpret_cast<float*>(0x00e50e44);
        }

        // Check if timer reached max and speed is significant
        bool stopFlag = false;
        bool decelFlag = false;
        if (g_springTimer >= *reinterpret_cast<float*>(0x00e50e44)) {
            float speedMag = stateFloats[0x68 / 4];
            if (speedMag * speedMag > 0.0f) {
                float speedAbs = fabs(speedMag);
                // Complex threshold check using constants
                float threshold_lo = *reinterpret_cast<float*>(0x00e50e54);
                float threshold_hi = *reinterpret_cast<float*>(0x00e50e50);
                float factor = 0.0f;
                if (threshold_lo <= speedAbs && speedAbs <= threshold_hi) {
                    factor = (threshold_hi - speedAbs) / (threshold_hi - threshold_lo);
                }
                float noise = 0.0f;
                if (noiseThreshold < speedMag * currentSpeed) {
                    noise = *reinterpret_cast<float*>(0x00d5842c);
                }
                float speedAbs_ = fabs(speedAbs);
                // Another threshold
                float threshold_low2 = *reinterpret_cast<float*>(0x00e50e48);
                float threshold_high2 = *reinterpret_cast<float*>(0x00e50e4c);
                float checkVal = noise * ((threshold_high2 - threshold_low2) * factor + threshold_low2);
                if (speedAbs_ < (threshold_hi - threshold_lo) * factor + threshold_lo ||
                    checkVal <= fabs(newSpeed)) {
                    stopFlag = false;
                } else {
                    stopFlag = true;
                    if (speedMag * currentSpeed <= 0.0f) {
                        if (stateFloats[0x6c / 4] > 0.0f) {
                            float ratio = speedMag / stateFloats[0x6c / 4];
                            if (ratio * ratio < *reinterpret_cast<float*>(0x00d5efc8)) {
                                stopFlag = false;
                                decelFlag = true;
                            }
                        }
                    } else {
                        stopFlag = false;
                        decelFlag = true;
                    }
                }
                // Reset accumulators
                stateFloats[0x68 / 4] = 0.0f;
                stateFloats[0x6c / 4] = 0.0f;
                stateFloats[0x70 / 4] = 0.0f;
            }
        }

        // Update timer
        stateFloats[0x58 / 4] -= deltaTime;
        float speedSq = newSpeed * newSpeed;
        float prevSpeedSq = stateFloats[0x54 / 4] * stateFloats[0x54 / 4];
        bool speedLow = speedSq < *reinterpret_cast<float*>(0x00d5efc4);
        float timer2 = stateFloats[0x5c / 4] + deltaTime;
        stateFloats[0x5c / 4] = timer2;
        bool timer2Reached = *reinterpret_cast<float*>(0x00e50e30) <= timer2;
        bool timer2Reached2 = *reinterpret_cast<float*>(0x00e50e34) <= timer2;

        bool overshoot = false;
        if (speedSq < prevSpeedSq &&
            *reinterpret_cast<float*>(0x00d5efc0) < newPrev * newPrev &&
            newPrev * newSpeed > 0.0f) {
            overshoot = true;
        }

        char debugFlag = 0;
        stateFloats[0x54 / 4] = newSpeed;
        stateFloats[0x50 / 4] = deltaTimeFromClock;
        float speedSqCurr = speedSq;

        // Debug hash check
        if (checkDebugHash(0xd378ba0f) == 0) {
            debugFlag = 1;
            if (self[0x3c] == 0) goto LAB_006c2431;
        } else {
            debugFlag = 0;
            // flag set
        LAB_006c2431:
            // Some branch
        }

        self[0x3c] = debugFlag;
        char slowFlag = 0;
        if (self[0x38] != 0 &&
            speedSqCurr <= *reinterpret_cast<float*>(0x00e50e08) * *reinterpret_cast<float*>(0x00e50e08)) {
            slowFlag = 1;
            if (*reinterpret_cast<float*>(0x00e50e04) * *reinterpret_cast<float*>(0x00e50e04) <
                stateFloats[0x34 / 4] * stateFloats[0x34 / 4]) {
                slowFlag = 0;
            }
        }

        bool useShift = false;
        stateFloats[0x34 / 4] = 0.0f;
        self[0x38] = 0;
        float shiftFactor = 0.0f;

        // Input manager again for shift detection
        if (inputMgr != nullptr) {
            float shiftValue;
            // get shift value from input manager
            // (virtual function call)
            void* vtable = *(void**)inputMgr;
            float inputShift; // local_2c
            // call (*(code**)(vtable+0x4c))(&inputShift);
            // Simulated:
            inputShift = 0.0f; // placeholder

            double rawTime2 = *(double*)(getFrameTime() + 0x20);
            // convert to float components
            float timeLow = (float)(unsigned long long)rawTime2;
            float timeHigh = (float)((unsigned long long)rawTime2 >> 32);
            // dot product? complex
            float dot = inputShift * timeHigh + timeLow * 0.0f; // simplified
            // Check debug flag
            char* debugStr = reinterpret_cast<char*>(getSomeDebugString()); // FUN_00549a40
            useShift = (debugStr[0] != 0);
            shiftFactor = dot;
        }

        float identityW2 = identityW; // likely 1.0
        bool shiftFlag = false;
        bool otherFlag = false;
        if (useShift) {
            char shiftState = 0;
            if (self[0x3a] != 0) {
                bool cond = identityW2 < shiftFactor;
                float val = identityW2;
                if (cond || val == shiftFactor) {
                    otherFlag = false;
                    shiftState = 0;
                } else {
                    otherFlag = true;
                    shiftState = 1; // depends on local_5d
                }
            }
        } else {
            char shiftState = 0;
            if (self[0x3a] == 0) {
                bool cond = shiftFactor < noiseThreshold;
                float val = noiseThreshold;
                // branch...
            }
        }

        // Determine if we need to reset to active state
        bool shouldReset = false;
        if ( (!someCondition) ) {
            // check various conditions
            if (speedSqCurr <= prevSpeedSq && timerReached) // etc.
            {
                shouldReset = true;
            }
        }

        // Combine flags
        char finalFlag = 0;
        if (shouldReset) {
            self[0x30] = 1;
            stateFloats[0x34 / 4] = 0.0f;
            self[0x38] = 1;
            self[0x39] = 0;
            self[0x3c] = 0;
            stateFloats[0x60 / 4] = 0.0f;
            // Use active constant
            float activeValue = *reinterpret_cast<float*>(0x00e50e0c);
            updateSmoothing(); // with local_44
            goto LAB_006c26b1;
        }

        if (finalFlag != 0) {
            // Handle other flags
            if (slowFlag != 0) {
                stateFloats[0x60 / 4] = *reinterpret_cast<float*>(0x00e50e38) * *reinterpret_cast<float*>(0x00d5c458);
            }
            self[0x39] = 1;
            stateFloats[0x60 / 4] += deltaTime;
            float ratio = stateFloats[0x60 / 4] / *reinterpret_cast<float*>(0x00e50e38);
            if (ratio < noiseThreshold) ratio = noiseThreshold;
            float interpolated = (*reinterpret_cast<float*>(0x00e50e1c) - *reinterpret_cast<float*>(0x00e50e18)) * ratio + *reinterpret_cast<float*>(0x00e50e18);
            // Use interpolated value
            updateSmoothing();
            goto LAB_006c26b1;
        }

        // Reset timer if needed
        if (stateFloats[0x60 / 4] > 0.0f) {
            stateFloats[0x60 / 4] = 0.0f;
            stateFloats[0x40 / 4] = 0.0f;
            stateFloats[0x44 / 4] = 0.0f;
            stateFloats[0x48 / 4] = identityW2;
        }

    } else {
        // Active state (offset 0x30 != 0)
        if (!isPaused) {
            // If not paused, handle resetting to idle
            if (inputAccel != 0.0f) {
                self[0x30] = 0; // deactivate
                self[0x39] = 0;
                self[0x3c] = 0;
                stateFloats[0x60 / 4] = 0.0f;
                stateFloats[0x4c / 4] = deltaTimeFromClock;
                stateFloats[0x54 / 4] = deltaTimeFromClock;
                stateFloats[0x50 / 4] = 0.0f;
                stateFloats[0x58 / 4] = identityW;
                stateFloats[0x5c / 4] = 0.0f;
                stateFloats[0x68 / 4] = 0.0f;
                stateFloats[0x6c / 4] = 0.0f;
                stateFloats[0x70 / 4] = 0.0f;
                g_springTimer = 0.0f;
            }
            goto LAB_006c1ff1;
        } else {
            // Paused or other condition -> go to active setup
        }
    }

    // Label from activation branch
LAB_006c1f3f:
    self[0x30] = 1;
    stateFloats[0x34 / 4] = 0.0f;
    self[0x38] = 1;
    self[0x39] = 0;
    self[0x3c] = 0;
    stateFloats[0x60 / 4] = 0.0f;
    // Use different constants
    float activeValue = *reinterpret_cast<float*>(0x00e50e14);
    if (inputAccel == 0.0f) {
        updateSmoothing();
        activeValue = *reinterpret_cast<float*>(0x00e50e0c);
        goto LAB_006c26b1;
    }
    if (self[0x3a] != 0) {
        inputAccel = *reinterpret_cast<float*>(0x00e44564) - inputAccel;
    }
    inputAccel = inputAccel * *reinterpret_cast<float*>(0x00e446a0);
    // Set rotation
    stateFloats[0x40 / 4] = 0.0f;
    stateFloats[0x44 / 4] = 0.0f;
    stateFloats[0x48 / 4] = identityW;
    float newAngle = clampAngle(inputAccel + deltaTimeFromClock);
    // Apply rotation
    rotateVectorByQuaternion(&stateFloats[0x40 / 4], &stateFloats[0x40 / 4], nullptr, newAngle);

    // Common exit point
LAB_006c26b1:
    // Compute final output vector
    double finalDelta = (double)(*reinterpret_cast<float*>(0x00e44564) - stateFloats[0x40 / 4]);
    syncTime();
    float temp[4] = {(float)finalDelta, 0.0f, 0.0f, 0.0f};
    float outputScale = activeValue;
    // Check if there is a transition timer at offset 100
    if (stateFloats[100 / 4] != identityW) {
        float transitionTimer = stateFloats[100 / 4] + deltaTime;
        stateFloats[100 / 4] = transitionTimer;
        float ratio = transitionTimer / *reinterpret_cast<float*>(0x00e50e3c);
        if (ratio < noiseThreshold) ratio = noiseThreshold;
        outputScale = (*reinterpret_cast<float*>(0x00e50e24) - *reinterpret_cast<float*>(0x00e50e20)) * ratio + *reinterpret_cast<float*>(0x00e50e20);
    }
    // Set structure header (maybe a VTable? not used)
    // * (uint16_t*)self = DAT_00e50df6; (assuming little endian)
    *(float*)(self + 4) = outputScale;
    *(float*)(self + 8) = *reinterpret_cast<float*>(0x00e50e28);

    // Integrate spring motion
    integrateSpring(temp, deltaTime);

    // Build output direction (default up vector)
    outDirection[0] = 0.0f;
    outDirection[1] = 0.0f;
    outDirection[2] = identityW;
    // Rotate by angle from temp[0]
    float angle = clampAngle(temp[0]);
    rotateVectorByQuaternion(outDirection, outDirection, nullptr, angle);

    // Check for transition end
    if (stateFloats[100 / 4] != identityW) {
        float diff = clampAngle(deltaTimeFromClock - temp[0]);
        if (diff * diff < *reinterpret_cast<float*>(0x00e50e58) * *reinterpret_cast<float*>(0x00e50e58)) {
            stateFloats[100 / 4] = identityW;
        }
    }

    // Update current value if flag set
    if (self[0x39] != 0) {
        stateFloats[0x4c / 4] = temp[0];
    }

    // Scale output by identityW (usually 1.0)
    outDirection[0] *= identityW;
    outDirection[1] *= identityW;
    outDirection[2] *= identityW;
    return;
}