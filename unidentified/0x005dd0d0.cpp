// FUN_NAME: CameraInterpolator::init
void CameraInterpolator::init(float targetX, float targetY, float targetZ) {
    // Retrieve source and destination data pointers from internal state
    // Helper returns a 64-bit value: lower 32 bits = destData, upper 32 bits = srcData
    uint64_t ptrPair = getInterpolatorData();
    float* destData = (float*)(ptrPair & 0xFFFFFFFF);
    float* srcData = (float*)(ptrPair >> 32);

    float maxValue = DAT_00e2b1a4;               // Global max clamp value
    float minSpeedThreshold = DAT_00e44598;      // Global minimum speed for interpolation
    float negativeIntFix = DAT_00e44578;         // ~4294967296.0f for signed int conversion

    // Validation: check bounds on source data
    if (srcData[0] <= maxValue &&
        srcData[1] <= maxValue &&
        srcData[2] <= maxValue &&
        (srcData[5] > 0.0f || (srcData[5] == 0.0f && (srcData[6] > 0.0f || srcData[6] == 0.0f))) &&
        (srcData[3] >= 0.0f && (srcData[4] > 0.0f || (srcData[4] == 0.0f && (uint)srcData[13] < 0x17701)))) {

        // Set initial position values
        if (srcData[0] < 0.0f) {
            destData[0] = srcData[3];      // +0x00: x position
        } else {
            destData[0] = srcData[0];
        }

        if (srcData[4] <= 0.0f) {
            *(uint8_t*)((int)destData + 0x21) = 1;   // +0x21: flag (use source[3] for x)
        } else {
            destData[1] = srcData[4];                 // +0x04: y position
            *(uint8_t*)((int)destData + 0x21) = 0;
        }

        // Set frame count / time value
        if ((uint)srcData[13] < 0x17701) {
            destData[17] = srcData[13];              // +0x44: time or frame count
        } else {
            destData[17] = 1.34525e-40f;             // Invalid small float
        }

        // Clamp position x
        if (destData[0] > maxValue) {
            destData[0] = maxValue;
        } else if (destData[0] < 0.0f) {
            destData[0] = 0.0f;
        }

        // Clamp time
        if ((uint)destData[17] > 96000) {
            destData[17] = 1.34525e-40f;
        }

        destData[2] = srcData[5];                    // +0x08: some speed/rate value

        bool isSlow = destData[2] < minSpeedThreshold;

        destData[10] = targetX;                      // +0x28: target x
        destData[11] = targetZ;                      // +0x2C: target z (from XMM4)
        destData[16] = targetY;                      // +0x40: target y
        destData[9] = 0.0f;                          // +0x24: initial velocity component

        if (isSlow) {
            // Slow interpolation: no velocity
            destData[12] = 0.0f;                     // +0x30: delta x velocity
            destData[13] = 0.0f;                     // +0x34: delta y velocity
            destData[18] = 0.0f;                     // +0x48: delta z velocity
        } else {
            // Compute interpolation velocities
            float timeAsFloat = (float)(int)destData[17];
            if ((int)destData[17] < 0) {
                timeAsFloat += negativeIntFix;
            }

            float invSpeed = maxValue / destData[2];

            destData[12] = (destData[0] - targetX) * invSpeed;
            destData[13] = (destData[1] - targetZ) * invSpeed;

            float targetYAsFloat = (float)(int)targetY;
            if ((int)targetY < 0) {
                targetYAsFloat += negativeIntFix;
            }
            destData[18] = (timeAsFloat - targetYAsFloat) * invSpeed;
        }

        *(uint8_t*)((int)destData + 0x23) = 0;       // +0x23: flag (interpolation mode)

        // Copy remaining source attributes
        destData[3] = srcData[7];                     // +0x0C: attribute 4
        destData[4] = srcData[8];                     // +0x10: attribute 5
        destData[5] = srcData[9];                     // +0x14: attribute 6
        destData[6] = srcData[10];                    // +0x18: attribute 7
        destData[7] = srcData[11];                    // +0x1C: attribute 8
        *(uint8_t*)(destData + 8) = *(uint8_t*)(srcData + 12); // +0x20: byte attribute

        *(uint8_t*)((int)destData + 0x22) = 0;       // +0x22: flag (clear)
    }
}