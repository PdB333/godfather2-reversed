// FUNC_NAME: clampedApproachStep
float FUN_00410eb0(); // returns non-zero if some condition met (e.g., random check)

float clampedApproachStep(float currentValue, float step)
{
    // DAT_00e44680 likely holds bitmask 0x7FFFFFFF for absolute value extraction
    const unsigned int absMask = 0x7FFFFFFF;
    float absCurrent = (float)(*(unsigned int*)&step & absMask); // equivalent to fabsf(step)
    float absStep = (float)(*(unsigned int)¤tValue & absMask); // equivalent to fabsf(currentValue)
    
    // Compare absolute values
    if (absStep <= absCurrent) {
        float delta = currentValue - step;  // (param_1 - param_2)
        float absDelta = fabsf(delta);
        
        float threshold = *((float*)0x00e510f4); // default clamp threshold
        if (FUN_00410eb0() != 0) {
            threshold = *((float*)0x00e510c4); // alternative threshold
        }
        
        // Clamp delta magnitude to at most threshold (scale down if larger)
        if (threshold < absDelta) {
            delta = (threshold / absDelta) * delta;
        }
        
        // Return (clamped delta) + step as extended precision float
        return (double)delta + (double)step;
    }
    
    // No modification if step is larger in magnitude than current
    return (double)currentValue;
}