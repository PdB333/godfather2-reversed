// FUNC_NAME: CyclicBlendInterpolator::advanceBlend
void __thiscall CyclicBlendInterpolator::advanceBlend(float *this, float deltaTime, bool bLoop, uint flags)
{
    // Offsets: this[0] = m_currentValue (float), this[1] = m_fromIndex, this[2] = m_toIndex, this[3] = m_blendFactor, this[4] = m_bWrapDirection (bool)
    // Global constants: s_frameTime (DAT_00e2b1a4), s_thresholdA (DAT_00e2cd54), s_thresholdB (DAT_00e2b334), s_thresholdC (DAT_00e4461c), s_unknownVal (DAT_00e44564), s_mask (DAT_00e44680)
    // unaff_EDI is an implicit integer parameter representing the total frame count (likely stored in EDI by caller)

    float frameTime = DAT_00e2b1a4; // base frame time
    float inputParam; // in_XMM3_Da
    if (inputParam < 0.0f) {
        if (!bLoop || !(deltaTime <= frameTime)) {
            do {
                inputParam = (deltaTime - frameTime) + inputParam; // wrap inputParam into non-negative range
            } while (inputParam < 0.0f);
        } else {
            inputParam = 0.0f;
        }
    }

    float invScaled = frameTime / deltaTime;
    float scaledValue = invScaled * inputParam; // this[0] = scaled value
    this[0] = scaledValue;

    int totalFrames = unaff_EDI; // total number of frames (passed implicitly)
    if (totalFrames < 1 || scaledValue < (float)(totalFrames - 1)) {
        this[1] = (float)(int)scaledValue;
        if ((int)scaledValue < 0) {
            this[1] = 0.0f;
        }
        float fractional = scaledValue - (float)(int)this[1];
        // next index with wrap
        this[2] = (float)(((int)this[1] + 1) % (int)deltaTime);
        goto storeFraction;
    } else {
        // handle case where scaledValue is near the end
        float remainder = (scaledValue - (float)totalFrames) + frameTime;
        this[1] = (float)(totalFrames - 1);
        this[2] = 0.0f;
        if (remainder == 0.0f) {
            this[3] = 0.0f;
        } else {
            float divisor = ((deltaTime - frameTime) * invScaled - (float)totalFrames) + frameTime;
            if (divisor != 0.0f) {
                fractional = remainder / divisor;
                goto storeFraction;
            }
            this[3] = 0.0f;
        }
        return; // early exit? no, continues
    }

storeFraction:
    this[3] = fractional; // blend factor

    // Determine wrap direction based on indices
    this[4] = (bool)((int)this[2] < (int)this[1]); // true if m_toIndex < m_fromIndex (reverse wrap)
    if ((int)this[2] < (int)this[1] && bLoop == false) {
        // if not looping and wrapped, adjust to correct values
        this[2] = this[1];
        this[0] = (float)totalFrames - frameTime;
        this[4] = 0; // reset direction
    }

    // Apply flag-based adjustments
    float threshold = DAT_00e2cd54; // default threshold
    if ((flags & 0x8000) == 0) {
        threshold = DAT_00e2b334;
        if ((flags & 0x4000) != 0) {
            threshold = DAT_00e4461c;
        }
    }

    // Compare with masked difference to decide clamping
    uint maskedDiff = (uint)(DAT_00e44564 - this[3]) & DAT_00e44680;
    if (threshold < (float)maskedDiff) {
        if (threshold <= (float)((uint)(frameTime - this[3]) & DAT_00e44680)) {
            goto label_end;
        }
        // clamp to current m_toIndex
        this[1] = this[2];
    } else {
        // clamp to current m_fromIndex
        this[2] = this[1];
    }
    this[0] = (float)(int)this[1]; // set current value to integer part

label_end:
    if (this[1] == this[2]) {
        this[3] = 0.0f; // no blend if indices equal
        this[0] = (float)(int)this[1];
    }
}