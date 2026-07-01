// FUNC_NAME: VehicleController::updateThrottleInput
// Address: 0x007adff0
// This function reads analog input from two channels (likely left/right triggers or stick axes),
// applies sensitivity scaling, clamps to [minThrottle, maxThrottle], and smoothly updates the
// throttle state with a fixed step size per frame.

void __fastcall VehicleController::updateThrottleInput(void* thisPtr)
{
    float axis1 = 0.0f;
    float axis2 = 0.0f; // Stored in local_c high part + local_4 unused? We'll use axis2.
    // The original code used a union-like storage; we simplify.

    // Read first analog input (index 0) – yields axis1 and possibly other data.
    readAnalogInput(0, &axis1, &axis2, // Actually reads into axis1 and a 64-bit area; we treat as axis1 and axis2.
                    nullptr, nullptr, 
                    g_analogConstant1, g_analogConstant1, g_analogConstant1);

    // Read second analog input (index 1) – overwrites axis2.
    readAnalogInput(1, &axis2, &axis1, // last param ignored.
                    nullptr, nullptr,
                    g_analogConstant1, g_analogConstant1, g_analogConstant1);

    // Combine both axes (sum) and multiply by sensitivity.
    float rawTarget = (axis1 + axis2) * g_sensitivity; // _DAT_00d5c458

    // Clamp target to valid range [g_minThrottle, g_maxThrottle].
    float target;
    if (rawTarget < g_minThrottle) {
        target = g_minThrottle;
    } else if (rawTarget > g_maxThrottle) {
        target = g_maxThrottle;
    } else {
        target = rawTarget;
    }

    // Read current throttle from member (this+0x58 gives pointer to sub-object +0x2894).
    float* pCurrentThrottle = (float*)(*(int*)((uintptr_t)thisPtr + 0x58) + 0x2894);
    float current = *pCurrentThrottle;

    // Step towards target by g_throttleStep.
    float delta = g_throttleStep; // _DAT_00d5cf70
    if (current < target) {
        if (target - current > delta) {
            applyThrottle(current + delta);
        } else {
            applyThrottle(target);
        }
    } else if (current > target) {
        if (current - target > delta) {
            applyThrottle(current - delta);
        } else {
            applyThrottle(target);
        }
    }
    // If equal, nothing to do.
}

// Called functions:
// void readAnalogInput(int index, float* out1, float* out2, int* param4, int* param5,
//                      float constant1, float constant2, float constant3);
// Reads analog input from controller axis/trigger selected by index. Returns values in out1, out2.
// void applyThrottle(float value); // Sets or ramps throttle output to the given value.

// Global constants (e.g., g_sensitivity (0x00d5c458), g_minThrottle (0x00d6bbf8),
// g_maxThrottle (0x00e446dc), g_throttleStep (0x00d5cf70),
// g_analogConstant1 (0x00d5ccf8) – possibly dead zone or scaling factor).