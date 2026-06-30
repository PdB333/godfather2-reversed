// FUNC_NAME: AudioRamp::update
void __thiscall AudioRamp::update(int *this, float dt)
{
    int mode = this[0]; // +0x00: interpolation mode (0=step, 1=linear, 2=exponential)
    float *pCurrentValue = (float *)this[1]; // +0x04: pointer to current value
    float *pTargetValue = (float *)this[2]; // +0x08: pointer to target value
    float rate = *(float *)&this[3]; // +0x0c: ramp rate or time constant
    float param4 = *(float *)&this[4]; // +0x10: additional parameter (e.g., start value or exponent)

    if (mode == 0) {
        // Step mode: immediate jump to target or discrete increment
        unsigned char stepResult = AudioRamp::computeStep(pTargetValue, &param4, dt); // 0x006ebff0
        AudioRamp::applyStep(pCurrentValue, pTargetValue, dt, stepResult); // 0x006eb810
    }
    else if (mode == 1) {
        // Linear interpolation
        float linearResult = AudioRamp::computeLinear(pTargetValue, &param4, dt); // 0x006eb7b0
        AudioRamp::applyLinear(pCurrentValue, pTargetValue, dt, linearResult); // 0x006eb820
    }
    else if (mode == 2) {
        // Exponential interpolation (uses double internally)
        double expResult = (double)AudioRamp::computeExponential(pTargetValue, &param4, dt); // 0x006eb7c0 returns float10 (double)
        AudioRamp::applyExponential(pCurrentValue, pTargetValue, dt, (float)expResult); // 0x006eb830
    }
    // mode other values: no action
    return; // original returns 0, but we treat as void
}