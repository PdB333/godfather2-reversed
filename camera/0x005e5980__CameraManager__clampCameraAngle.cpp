// FUNC_NAME: CameraManager::clampCameraAngle
void __fastcall clampCameraAngle(int mode, float factor, float* inputAngles, float* output) 
{
    // Constants from global data (addresses):
    // DAT_00e2cd54: g_threshold       (0x00e2cd54)
    // DAT_00e2b1a4: g_maxAngle        (0x00e2b1a4)
    // DAT_00e2eff4: g_minAngle        (0x00e2eff4)
    // DAT_00e44564: g_angleOffset     (0x00e44564)
    // DAT_00e2afac: g_outputMax       (0x00e2afac)
    // DAT_00e2a848: g_angleWrap       (0x00e2a848)

    const float kThreshold = *(float*)0x00e2cd54;
    const float kMaxAngle  = *(float*)0x00e2b1a4;
    const float kMinAngle  = *(float*)0x00e2eff4;
    const float kAngleOff  = *(float*)0x00e44564;
    const float kOutputMax = *(float*)0x00e2afac;
    const float kWrap      = *(float*)0x00e2a848;

    if (mode == 1)
    {
        *output = 0.0f;

        // Only proceed if factor exceeds threshold
        if (kThreshold < factor)
        {
            float invFactor = kMaxAngle / factor; // DT_00e2b1a4 / factor

            // Compute two potential offsets
            float offset1 = kAngleOff - inputAngles[0] * invFactor; // X-component scaling
            float offset2 = inputAngles[2] * invFactor;             // Z-component scaling

            // Clamp offset1 to [kMinAngle, kMaxAngle]
            float clamped = kMinAngle;
            if (kMinAngle < offset1)
            {
                clamped = offset1;
                if (kMaxAngle <= offset1)
                {
                    clamped = kMaxAngle;
                }
            }

            // Condition based on offset2
            if ((offset2 <= kMinAngle) || ((offset2 < kMaxAngle) && (offset2 <= 0.0f)))
            {
                // Convert to double and call helper (likely FPU rounding/setup)
                double dVal = (double)clamped;
                FUN_00b9c766(); // Call to some floating-point utility function
                *output = kOutputMax - (float)dVal;
            }
            else
            {
                double dVal = (double)clamped;
                FUN_00b9c766();
                float val = (float)dVal;
                *output = val;
                if (val < 0.0f)
                {
                    *output = val + kWrap;
                }
            }
        }
    }
    else
    {
        *output = 0.0f;
    }
}