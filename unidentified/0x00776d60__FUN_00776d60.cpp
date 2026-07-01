// FUNC_NAME: SomeClass::isWithinTolerance
undefined1 __thiscall SomeClass::isWithinTolerance(int thisPtr, float param_2)
{
    float halfWidth;
    float10 randomFactor;
    float interpolatedHalfWidth;
    float baseHalfWidth;

    // Read base half-width from object at offset 0xB0
    baseHalfWidth = *(float *)(thisPtr + 0xB0);
    // Compute difference from global target value (DAT_00d68268)
    halfWidth = DAT_00d68268 - baseHalfWidth;
    if (halfWidth <= 0.0f) {
        halfWidth = 0.0f;
    }
    // Get random factor from helper function (likely returns 0.0-1.0)
    randomFactor = (float10)FUN_00776cd0();
    // Interpolate half-width: base + random * difference
    interpolatedHalfWidth = (float)(randomFactor * (float10)halfWidth + (float10)baseHalfWidth);

    // Choose constant based on whether param_2 exceeds a threshold (DAT_00d5eeec)
    float constant;
    if (DAT_00d5eeec <= param_2) {
        constant = DAT_00d68264;
    } else {
        constant = DAT_00d5f00c;
    }

    // Check if param_2 is within [constant - interpolatedHalfWidth, constant + interpolatedHalfWidth]
    if (param_2 < constant - interpolatedHalfWidth) {
        return 0;
    }
    if (interpolatedHalfWidth + constant < param_2) {
        return 0;
    }
    return 1;
}