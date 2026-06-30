// FUNC_NAME: SteeringController::computeSteeringBlendFactor
// Address: 0x006c3e70
// This function computes a steering blend factor for an agent given current and target positions.
// It uses player input, a stored previous steering value, and various thresholds and blends.

#include <cmath>

// Forward declarations of called functions
float __fastcall getPlayerSpeed(int playerPtr);  // FUN_006c93c0
float __fastcall getPreviousSteeringForce();     // FUN_006c3d70
void __fastcall normalizeVector(float* vec);      // FUN_0056afa0
float __fastcall dotProduct3(float* a, float* b); // FUN_0043a210
void __fastcall mathSinCosWrapper();            // FUN_00b9b988 (likely)
void __fastcall mathClampWrapper(float* result, float value, float min, float max); // for clarity
float __fastcall lerp(float a, float b, float t); // FUN_006c91c0

// Global constants (from data references)
extern float DAT_00d5ef90;      // some threshold or base value
extern float DAT_00d58cbc;      // speed threshold
extern float DAT_00d5efe0;      // min dot
extern float DAT_00d5efd4;      // alternative min
extern float DAT_00d577a0;      // another threshold
extern float DAT_00d5efdc;      // subtractor
extern float DAT_00d5efd8;      // multiplier
extern float DAT_00d5c454;      // another threshold
extern float DAT_00e50e6c;      // epsilon for distance
extern float DAT_00d5780c;      // max clamp value (1.0f?)
extern float DAT_00e44598;      // comparison threshold
extern float DAT_00e44564;      // constant for division
extern float DAT_00d5eea0;      // min clamp
extern float DAT_00e44940;      // multiplier
extern float DAT_00d5efe4;      // lower bound for LERP
extern float DAT_00d5eecc;      // upper bound for LERP
extern float DAT_00e445a0;      // blend target

// Player manager singleton (assumed)
int* __fastcall getPlayerManager(); // FUN_00471610

// Debug check
char* __fastcall debugCheckParameter(int* param); // FUN_00549a30

class SteeringController {
public:
    // Offsets (from param_1 + offset)
    // +0x7c: bool flag (enableSteering?)
    // +0xe8: pointer to component (e.g., VehicleBrain)
    // +0x2c0: float previousSteeringForce
    // +0x2c4: float storedSpeed
    // +0x2bc (700): bool useAlternativeMode

    float computeSteeringBlendFactor(float* currentPos, float* targetPos) {
        float blendFactor = 0.0f;
        float threshold = DAT_00d5ef90; // initial threshold

        if (*(char*)(this + 0x2bc) == 0) {
            // Standard mode
            if (*(char*)(this + 0x7c) != 0) {
                // Get speed from linked component (offset 0xe8 -> component pointer - 0x48)
                int compPtr = *(int*)(this + 0xe8);
                if (compPtr != 0) {
                    compPtr -= 0x48;
                }
                float speed = getPlayerSpeed(compPtr);
                if (DAT_00d58cbc < speed) {
                    float playerDot;
                    int* playerMgr = getPlayerManager();
                    // Player forward vector (from player manager at +0x20)
                    float* forward = (float*)(playerMgr + 0x20);
                    float dx = targetPos[0] - currentPos[0];
                    float dz = targetPos[2] - currentPos[2];
                    float dir[3] = {dx, 0.0f, dz};
                    // Actually uses player forward and up? The code uses local_2c (8 bytes) as a vec2? It's messy.
                    // Reconstructing: local_2c = *(ulonglong*)(playerMgr+0x20) & 0xffffffff
                    // meaning it takes x and y of player forward? (platform endian issues)
                    // For clarity, treat as dot product of (dx, dz) with (forward[0], forward[1])? Actually playerMgr+0x20 is likely a 3-vector.
                    // Simpler: call dot product function.
                    float fwdX = *(float*)(playerMgr + 0x20);
                    float fwdY = *(float*)(playerMgr + 0x24);
                    float fwdZ = *(float*)(playerMgr + 0x28);
                    // dot product (dx, 0, dz) with (fwdX, fwdY, fwdZ) – but code uses dx*fwdX + dz*fwdZ (ignores Y)
                    float dot = dx * fwdX + dz * fwdZ; // approximated
                    if (dot <= DAT_00d5efe0) {
                        blendFactor = DAT_00d5efd4;
                        if (DAT_00d577a0 < dot) {
                            // Clamp and scale
                            double dDot = (double)dot;
                            // calling math sin/cos? Actually FUN_00b9b988 might be sin/cos setup? Skip.
                            blendFactor = ((float)dDot - DAT_00d5efdc) * DAT_00d5efd8;
                        }
                    } else {
                        blendFactor = 0.0f;
                    }
                }
                blendFactor = blendFactor; // local_4c gets this
                threshold = DAT_00d5c454;
            }
        } else {
            // Alternative mode (when flag at 0x2bc is set)
            float dx = targetPos[0] - currentPos[0];
            float dz = targetPos[2] - currentPos[2];
            float dist = sqrt(dx*dx + dz*dz);

            // Call a virtual method on linked component to get an offset vector
            int compPtr = *(int*)(this + 0xe8);
            if (compPtr != 0) {
                compPtr -= 0x48;
            }
            // Virtual call at vtable+0x4c (expected signature: void getSteerDirection(float *out))
            float steerDir[3];
            (*(void (__thiscall**)(int, float*))(*(int*)compPtr + 0x4c))(compPtr, steerDir);

            float steerMag = sqrt(steerDir[0]*steerDir[0] + steerDir[2]*steerDir[2]); // using x and z

            int* playerMgr = getPlayerManager();
            float* playerForward = (float*)(playerMgr + 0x20);
            if (steerMag <= DAT_00e50e6c) {
                // Use player forward as steer direction
                steerDir[0] = playerForward[0];
                steerDir[1] = playerForward[1];
                steerDir[2] = playerForward[2];
                normalizeVector(steerDir);
            } else {
                float scale = DAT_00d5780c / steerMag;
                steerDir[0] *= scale;
                steerDir[1] *= scale; // but original may have different components
                steerDir[2] *= scale;
            }

            // Dot product of player forward with steer direction
            float dot = playerForward[0]*steerDir[0] + playerForward[1]*steerDir[1] + playerForward[2]*steerDir[2];
            if (dot >= 0.0f) {
                // Do something with threshold
                if (DAT_00e44598 < threshold) {
                    // Compute a factor based on dot product and distance
                    // Actually uses steerDir and playerForward again
                    // Reconstructed: use dot product of steerDir with something else
                    float dot2 = steerDir[0]*playerForward[0] + steerDir[1]*playerForward[1] + steerDir[2]*playerForward[2]; // same? 
                    // Not exactly; the code uses (DAT_00e44564 - (dz*steerDir[2] + dx*steerDir[0])) / threshold
                    float num = DAT_00e44564 - (dx*steerDir[0] + dz*steerDir[2]);
                    float factor = num / threshold;
                    // Clamp factor between DAT_00d5eea0 and DAT_00d5780c
                    if (factor <= DAT_00d5eea0) {
                        factor = DAT_00d5eea0;
                    } else if (DAT_00d5780c <= factor) {
                        factor = DAT_00d5780c;
                    }
                    double dFactor = (double)factor;
                    // Calling some math function (maybe trigonometric)
                    // Then get previous steering force
                    float prevForce = getPreviousSteeringForce();
                    *((float*)(this + 0x2c4)) = prevForce;
                    if (prevForce < factor) {
                        // Compute acceleration
                        float accel = (factor - prevForce) * DAT_00e44940;
                        if (DAT_00d5780c < accel) {
                            accel = DAT_00d5780c;
                        }
                        // uStack_50 becomes accel (but not directly used later? Possibly output)
                        // Actually uStack_50 is stored and later passed to some debugging function
                    }
                }
            } else {
                // Reset stored steering
                *(int*)(this + 0x2c0) = 0;
                // uStack_50 = 0.0f; (not captured)
            }

            // Check a condition via virtual call at +0x10 (with some hash)
            int compPtr2 = *(int*)(this + 0xe8);
            if (compPtr2 != 0) compPtr2 -= 0x48;
            bool condition = (*(bool (__thiscall**)(int, int, float*))(*(int*)compPtr2 + 0x10))(compPtr2, 0x197c1972, &threshold);
            if (condition && dist != 0.0f) {
                // debug check
                char* debugFlag = debugCheckParameter((int*)&threshold + 3); // dubious
                if (*debugFlag != 0 && DAT_00d5efe4 < threshold) { // fStack_48? Actually threshold is reused
                    // Clamp threshold
                    if (DAT_00d5eecc <= threshold) {
                        threshold = DAT_00d5eecc;
                    }
                    // Compute using lerp function
                    float lerpOut1 = lerp(threshold, DAT_00d5efe4, DAT_00d5eecc, 1.0f, DAT_00e445a0);
                    // actual call: FUN_006c91c0(fStack_48, _DAT_00d5efe4, DAT_00d5eecc, 0x3f800000, DAT_00e445a0)
                    // The lerp function maps threshold from [DAT_00d5efe4, DAT_00d5eecc] to [0x3f800000=1.0, DAT_00e445a0]
                    // Second lerp call:
                    float lerpOut2 = lerp(threshold, DAT_00d5efe4, DAT_00d5eecc, DAT_00d5ef90, DAT_00d5c454);
                    // Combine with previous steering force
                    float combined = *((float*)(this + 0x2c0)) * lerpOut1;
                    // Clamp combined
                    blendFactor = DAT_00d58cbc;
                    if (DAT_00d58cbc < combined && combined < DAT_00d5780c) {
                        blendFactor = combined;
                    }
                    goto LAB_006c4369;
                }
            }
        }

        // Normal return: blend between previous value and computed blendFactor
        finalBlend = lerp(threshold, 0.0f, 0.0f, *((float*)(this + 0x2c0)), blendFactor); // approximated
        // Actually return: fVar6 * local_4c + (1-fVar6) * *(float*)(param_1+0x2c0)
        // where fVar6 = local_44 (which is threshold at end) and local_4c = blendFactor

LAB_006c4369:
        return threshold * blendFactor + (1.0f - threshold) * *((float*)(this + 0x2c0));
    }
};