// FUNC_NAME: CameraSpring::updateState

void CameraSpring::updateState(float* targetData) // targetData passed in EAX, points to input struct with fields at offsets 0x00-0x44
{
    // Global state variables
    // g_springFlags (DAT_01219294) - bitmask: bit28=initialized, bit0=pitchChanged, bit1=yawChanged
    // g_springOutput[4] (DAT_01219250) - smoothed orientation (quaternion)
    // g_springVelocity[4] (DAT_01219260) - angular velocity vector (or target?)
    // g_springPos (DAT_01219270) - current position
    // g_springMaxPos (DAT_01219274) - maximum position
    // g_springMinVel (DAT_01219278) - minimum velocity
    // g_springMaxVel (DAT_0121927c) - maximum velocity
    // g_springMinAccel (DAT_01219280) - minimum acceleration
    // g_springMaxAccel (DAT_01219284) - maximum acceleration
    // g_springYawSpeed (DAT_01219288) - yaw speed
    // g_springPitchSpeed (DAT_0121928c) - pitch speed
    // g_springClampThreshold (DAT_01219290) - clamp value
    // g_springDeltaTime (DAT_0121925c) - time step (set at end)
    // g_springInputThreshold (DAT_00e2af44) - input validity threshold
    // g_springInputCenter[4] (DAT_00e2da30) - world center offset for input
    // g_springSmoothFactor (DAT_00e2b1a4) - smoothing factor (~deltaTime)
    // g_springLerpFactor (DAT_00e2cd54) - lerp factor (0..1)
    // g_springDefaultVal (DAT_00e39f98) - default float

    // Check if either the global flag or input flag indicates "first run" (bit28)
    if ((g_springFlags & 0x10000000) == 0 && ((uint32_t)targetData[0x11] & 0x10000000) == 0)
    {
        // Normal update: only if both sides are initialized
        // Check input validity based on certain fields (index 0xb, 0xe, 0xf)
        if ((g_springInputThreshold < targetData[0xb] || g_springInputThreshold == targetData[0xb]) &&
            (g_springInputThreshold < targetData[0xe] || g_springInputThreshold == targetData[0xe] ||
             (g_springInputThreshold < targetData[0xf] || g_springInputThreshold == targetData[0xf])))
        {
            // Check if global ranges are valid
            if (g_springInputThreshold <= g_springMaxVel &&
                (g_springInputThreshold <= g_springYawSpeed || g_springInputThreshold <= g_springPitchSpeed))
            {
                // Process orientation (indices 0..3)
                float clampVal = targetData[0x10];
                if ((int)targetData[0x10] < (int)g_springClampThreshold)
                {
                    clampVal = g_springClampThreshold;
                }

                // Blend input quaternion toward center, then clamp to previous output
                __m128 blendedQuat = _mm_set_ps(
                    (targetData[3] - g_springInputCenter[3]) * g_springSmoothFactor + g_springInputCenter[3],
                    (targetData[2] - g_springInputCenter[2]) * g_springSmoothFactor + g_springInputCenter[2],
                    (targetData[1] - g_springInputCenter[1]) * g_springSmoothFactor + g_springInputCenter[1],
                    (targetData[0] - g_springInputCenter[0]) * g_springSmoothFactor + g_springInputCenter[0]
                );
                g_springOutput[0] = _mm_min_ps(blendedQuat, g_springOutput[0]); // minps stores back
                // Note: g_springOutput is global __m128; the code only uses first 12 bytes? Actually it stores via _0_0_12_ which means three floats? Must be a bug in decompilation. We'll store all 4.
                g_springOutput = _mm_min_ps(blendedQuat, g_springOutput);

                g_springClampThreshold = clampVal;

                // Handle velocity (indices 4..7) if bit2 set in input
                if (((uint32_t)targetData[0x11] & 4) != 0)
                {
                    if ((g_springFlags & 4) == 0)
                    {
                        // First time: copy directly
                        g_springVelocity[0] = targetData[4];
                        g_springVelocity[1] = targetData[5];
                        g_springVelocity[2] = targetData[6];
                        g_springVelocity[3] = targetData[7];
                    }
                    else
                    {
                        // Lerp toward target
                        FUN_004af2c0(&g_springVelocity, targetData + 4, g_springLerpFactor, &g_springVelocity);
                    }
                }

                // Update scalar fields
                float maxVel = g_springMaxVel;
                float inputMaxVel = targetData[10];
                if (targetData[10] < g_springMinVel)
                {
                    inputMaxVel = g_springMinVel;
                }
                g_springMinVel = inputMaxVel;

                g_springPos = (targetData[8] + g_springPos) * g_springLerpFactor;

                float inputMaxPos = targetData[9];
                if (targetData[9] < g_springMaxPos)
                {
                    inputMaxPos = g_springMaxPos;
                }
                g_springMaxPos = inputMaxPos;

                float inputMinVel = targetData[0xb];
                float newMinVel = inputMinVel;
                if (inputMinVel < g_springMaxVel)
                {
                    newMinVel = g_springMaxVel;
                }
                g_springMaxVel = newMinVel;

                // Handle pitch/yaw speed changes when direction flags change
                if ((((uint32_t)targetData[0x11] ^ g_springFlags) & 3) != 0)
                {
                    if ((g_springFlags & 2) != ((uint32_t)targetData[0x11] & 2))
                    {
                        float baseVal;
                        if ((g_springFlags & 2) != 0)
                            baseVal = maxVel; // previous maxVel
                        else
                            baseVal = inputMinVel; // inputMaxVel

                        g_springYawSpeed = (g_springYawSpeed / newMinVel) * baseVal;
                    }

                    if ((g_springFlags & 1) != ((uint32_t)targetData[0x11] & 1))
                    {
                        float baseVal;
                        if ((g_springFlags & 1) != 0)
                            baseVal = maxVel;
                        else
                            baseVal = inputMinVel;

                        g_springPitchSpeed = (g_springPitchSpeed / newMinVel) * baseVal;
                    }
                }

                // Update scalar extremes
                float inputMinAccel = targetData[0xc];
                if (g_springMinAccel < targetData[0xc])
                    inputMinAccel = g_springMinAccel;
                g_springMinAccel = inputMinAccel;

                float inputMaxAccel = targetData[0xd];
                if (targetData[0xd] < g_springMaxAccel)
                    inputMaxAccel = g_springMaxAccel;
                g_springMaxAccel = inputMaxAccel;

                // Merge flags
                g_springFlags |= (uint32_t)targetData[0x11];

                // Store delta time
                g_springDeltaTime = g_springSmoothFactor;

                return;
            }
        }

        // Fallback: copy 20 floats (all fields) to global output
        for (int i = 0; i < 20; i++)
        {
            g_springOutput[i] = targetData[i]; // targetData and g_springOutput are float arrays
        }
        g_springDeltaTime = g_springSmoothFactor;
    }
    else
    {
        // Initialization branch: reset global state to defaults
        g_springPos = g_springDefaultVal;             // DAT_00e39f98
        g_springMaxPos = g_springDefaultVal;
        g_springVelocity[0] = 0.0f;
        g_springVelocity[1] = 0.0f;
        g_springVelocity[2] = 0.0f;
        g_springVelocity[3] = g_springSmoothFactor;  // DAT_00e2b1a4
        g_springOutput[1] = g_springSmoothFactor;     // DAT_01219254 = g_springSmoothFactor
        g_springOutput[0] = g_springSmoothFactor;     // DAT_01219250
        g_springOutput[2] = g_springSmoothFactor;     // DAT_01219258
        g_springMinVel = g_springDefaultVal2;         // DAT_00e445ac (may be another constant)
        g_springMaxVel = 0.0f;
        g_springClampThreshold = 0.0f;
        g_springMinAccel = 0.0f;
        g_springMaxAccel = 0.0f;
        g_springYawSpeed = g_springSmoothFactor;
        g_springPitchSpeed = g_springSmoothFactor;
        g_springFlags = 0x10000000;
        g_springDeltaTime = g_springSmoothFactor;
    }

    return;
}