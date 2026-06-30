// FUNC_NAME: MathUtils::smoothDamp
void MathUtils::smoothDamp(float* input, float* outResult, float* outVelocity, float* outAccel)
// input[0] = currentValue
// input[1] = targetValue
// input[2] = maxSpeed
// input[5] = currentVelocity? (used as flag)
// input[8] = deltaTime
// input[9] = smoothTime (or damping factor)
// input[10] = useAcceleration flag (if 0, else use other formula)
// Global constants (typical values):
// g_smoothMin = DAT_00e2eff4 (probably 0.0f)
// g_smoothMax = DAT_00e2b1a4 (probably 1.0f)
// g_one = DAT_00e44564 (1.0f)
// g_velocityLow = DAT_00e2a850 (maybe 0.0f)
// g_velocityHigh = DAT_00e446a0 (maybe 1.0f)
// g_accelThreshold = DAT_00e2b05c (some epsilon)
{
    float fVar1, fVar2, local_14;
    float fVar4;
    double dVar3;

    if (input[10] == 0.0f) {
        // Simple damping branch (no acceleration)
        fVar2 = input[8];   // deltaTime
        fVar1 = input[9];   // smoothTime
        if (fVar2 == 0.0f) {
            // Zero deltaTime: direct output based on current value
            if (fVar1 <= 0.0f) {
                local_14 = g_velocityLow; // 0.0
            } else {
                local_14 = g_velocityHigh; // 1.0
            }
            if (input[0] == 0.0f) {
                fVar2 = 0.0f;
                fVar1 = g_velocityLow;
                if (0.0f < input[2]) {
                    fVar1 = g_velocityHigh;
                }
            } else {
                dVar3 = (double)input[0];
                __fastcallAbs(); // FUN_00b9a9fa: fabs on double?
                fVar1 = g_one - (float)dVar3; // 1 - current
                fVar2 = 0.0f;
            }
        } else {
            // Non-zero deltaTime
            fVar4 = g_smoothMin;
            if ((g_smoothMin < fVar1) && (fVar4 = g_smoothMax, fVar1 < g_smoothMax)) {
                fVar4 = fVar1; // clamp smoothTime
            }
            dVar3 = (double)fVar4;
            __fastcallClamp(); // FUN_00b9c766: clamp double?
            local_14 = g_one - (float)dVar3;
            dVar3 = (double)local_14;
            __fastcallSign(); // FUN_00b99e20: sign/floor?
            fVar1 = g_velocityHigh;
            if (0.0f < (float)dVar3 * fVar2) {
                fVar1 = g_velocityLow;
            }
            if (input[5] == 0.0f) {
                fVar2 = g_velocityHigh;
                if (0.0f < input[1] * (float)dVar3) {
                    fVar2 = g_velocityLow;
                }
            } else {
                dVar3 = (double)input[1];
                __fastcallAbs();
                fVar2 = (float)dVar3;
            }
        }
    } else {
        // Acceleration-aware branch
        dVar3 = (double)input[8];
        __fastcallAbs();
        fVar1 = (float)dVar3; // abs(deltaTime)
        fVar2 = input[9];     // smoothTime
        // Clamp fVar2 to [g_smoothMin, g_smoothMax]
        if (fVar2 <= g_smoothMin) {
            fVar2 = g_smoothMin;
        } else if (g_smoothMax <= fVar2) {
            fVar2 = g_smoothMax;
        }
        dVar3 = (double)fVar2;
        __fastcallClamp();
        local_14 = g_one - (float)dVar3;
        if (input[5] == 0.0f) {
            fVar4 = input[1];
            if (fVar4 == 0.0f) {
                fVar2 = 0.0f;
            } else {
                dVar3 = (double)local_14;
                __fastcallSign();
                fVar2 = g_velocityHigh;
                if (g_accelThreshold < (float)dVar3 * fVar4) {
                    fVar2 = g_velocityLow;
                }
            }
        } else {
            dVar3 = (double)input[1];
            __fastcallAbs();
            fVar2 = (float)dVar3;
        }
    }

    // Write outputs
    if (outResult != nullptr) *outResult = fVar1;
    if (outAccel != nullptr) *outAccel = fVar2;
    if (outVelocity != nullptr) *outVelocity = local_14;
}