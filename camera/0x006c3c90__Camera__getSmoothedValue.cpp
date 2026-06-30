// FUNC_NAME: Camera::getSmoothedValue
long double __fastcall Camera::getSmoothedValue(Camera* this)
{
    long double result;
    long double fVar2;
    float local_4;

    // Check if direct override flag at offset +0x2bc (700 decimal) is set
    if (this->m_bUseDirect == 0) {
        // Normal smoothing branch
        // Get current and target values from offsets +0x110 and +0x114
        float fCurrent = this->m_fCurrentValue;    // +0x110
        float fTarget = this->m_fTargetValue;      // +0x114
        // First interpolation factor at +0x298
        float fBlend1 = this->m_fSmoothingFactor; // +0x298
        // Second interpolation factor at +0x80
        float fBlend2 = this->m_fAdditionalFactor; // +0x80

        // Blend: current + (target - current) * factor1
        float fInterp1 = (fTarget - fCurrent) * fBlend1 + fCurrent;
        // Blend again with the result minus original current
        result = (fInterp1 - fCurrent) * fBlend2 + fCurrent;

        // Check if there's a target object pointer at offset +0x88
        if (this->m_pTargetObject != NULL) {
            // Call external function to get some value from the target object
            fVar2 = (long double)getTargetValueFromObject(this->m_pTargetObject);
            // Blend with a global constant (DAT_00d5efcc) and the result
            fVar2 = fVar2 * ((long double)result - (long double)g_fDefaultSmooth) + (long double)g_fDefaultSmooth;
            // Final blend using smoothing factor again
            result = ((long double)result - fVar2) * (long double)this->m_fSmoothingFactor + fVar2;
        }
    } else {
        // Override branch (flag is non-zero)
        float fTimeDelta = this->m_fTimeDelta; // +0x2dc
        if (g_fTimeThreshold < fTimeDelta) {
            // Use a different interpolation: (value at +0x1d8 - value at +0x110) * (fTimeDelta - g_fTimeThreshold) + value at +0x110
            return (long double)((this->m_fAnotherValue - this->m_fCurrentValue) * (fTimeDelta - g_fTimeThreshold) + this->m_fCurrentValue);
        }
        // Otherwise, simple linear blend using time delta
        result = (long double)((this->m_fCurrentValue - this->m_fPreviousValue) * fTimeDelta + this->m_fPreviousValue);
    }
    return result;
}

// Offsets in Camera structure (0x0 base):
// +0x80  m_fAdditionalFactor (float)
// +0x88  m_pTargetObject (pointer to some game object, likely a sentient or entity)
// +0x110 m_fCurrentValue (float) - current smoothed value (e.g., camera arm length)
// +0x114 m_fTargetValue (float) - desired target value
// +0x1c8 m_fPreviousValue (float) - previous frame's value
// +0x1d8 m_fAnotherValue (float) - alternative value when override is active
// +0x298 m_fSmoothingFactor (float) - first blend factor
// +0x2bc (700) m_bUseDirect (char) - flag to use direct interpolation branch
// +0x2dc m_fTimeDelta (float) - time step used in override branch

// Global constants:
// DAT_00d5efcc -> g_fDefaultSmooth (float) - default smooth factor
// DAT_00d5780c -> g_fTimeThreshold (float) - threshold for switching interpolation in override

// External function at 0x006c1070: getTargetValueFromObject(void* obj) -> float10
// Presumably returns some value from the target object (e.g., its current look-at angle or distance).