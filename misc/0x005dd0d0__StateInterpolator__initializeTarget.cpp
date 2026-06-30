// FUNC_NAME: StateInterpolator::initializeTarget
void StateInterpolator::initializeTarget(float targetX, float targetY, float targetZ) {
    float clampMax;
    bool bUseVelocity;
    float invDuration;
    float* pDestData;
    float* pSourceData;
    float tmpFloat;

    // Retrieve the current interpolation state and source configuration
    uint64_t statePointers = getInterpolationStateSources(); // returns eax:edx
    pDestData = (float*)statePointers;        // low: destination fields
    pSourceData = (float*)(statePointers >> 32); // high: source configuration

    clampMax = gMaxValue; // DAT_00e2b1a4

    // Condition to proceed with initialization (complex check on source data)
    float fFirst = pSourceData[0];
    if (((((fFirst <= clampMax) &&
          (pSourceData[1] <= clampMax)) &&
         (pSourceData[2] <= clampMax)) &&
        ((0.0f < pSourceData[5] || (pSourceData[5] == 0.0f && (0.0f < pSourceData[6] || pSourceData[6] == 0.0f))))) &&
       ((0.0f <= pSourceData[3] && ((0.0f < pSourceData[4] || (pSourceData[4] == 0.0f && (uint)pSourceData[0xd] < 0x17701))))))
    {
        // Set start position X
        if (fFirst < 0.0f) {
            pDestData[0] = pSourceData[3];
        } else {
            pDestData[0] = fFirst;
        }

        // Set start position Y and flag
        if (pSourceData[4] <= 0.0f) {
            *((uint8_t*)pDestData + 0x21) = 1;
        } else {
            pDestData[1] = pSourceData[4];
            *((uint8_t*)pDestData + 0x21) = 0;
        }

        // Set duration (frame count) from source, clamped
        if ((uint)pSourceData[0xd] < 0x17701) {
            pDestData[0x11] = pSourceData[0xd];
        } else {
            pDestData[0x11] = 1.34525e-40f; // denormalized flag for zero? 
        }

        // Clamp position X to [0, clampMax]
        if (pDestData[0] <= clampMax) {
            if (pDestData[0] < 0.0f) {
                pDestData[0] = 0.0f;
            }
        } else {
            pDestData[0] = clampMax;
        }

        // Clamp duration (frame count) to max frame 96000
        if ((uint)pDestData[0x11] > 96000) {
            pDestData[0x11] = 1.34525e-40f;
        }

        pDestData[2] = pSourceData[5]; // speed/ inv? 
        bUseVelocity = (pDestData[2] >= gThreshold); // DAT_00e44598

        pDestData[10] = targetX;
        pDestData[0xb] = targetY;
        pDestData[0x10] = targetZ;
        pDestData[9] = 0.0f; // current time or progress

        if (!bUseVelocity) {
            // Zero out velocity components
            pDestData[0xc] = 0.0f;
            pDestData[0xd] = 0.0f;
            pDestData[0x12] = 0.0f;
        } else {
            // Compute interpolation velocities
            float fx = (float)(int)pDestData[0x11];
            if ((int)pDestData[0x11] < 0) fx += gIntToFloatRoundingCorrection; // DAT_00e44578
            float fz = (float)(int)targetZ;
            if ((int)targetZ < 0) fz += gIntToFloatRoundingCorrection;

            invDuration = clampMax / pDestData[2]; // clampMax as time multiplier? 
            pDestData[0xc] = (pDestData[0] - targetX) * invDuration;
            pDestData[0xd] = (pDestData[1] - targetY) * invDuration;
            pDestData[0x12] = (fx - fz) * invDuration;
        }

        *((uint8_t*)pDestData + 0x23) = 0; // flag
        pDestData[3] = pSourceData[7];   // extra vector components
        pDestData[4] = pSourceData[8];
        pDestData[5] = pSourceData[9];
        pDestData[6] = pSourceData[10];
        pDestData[7] = pSourceData[0xb];
        *((uint8_t*)(pDestData + 8)) = *((uint8_t*)(pSourceData + 0xc)); // flag
        *((uint8_t*)pDestData + 0x22) = 0; // another flag
    }
}