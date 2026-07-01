// FUNC_NAME: SomeTimedClass::addProgress
float __thiscall SomeTimedClass::addProgress(int thisPtr, float delta, undefined4 reason)
{
    float oldVal;
    float newVal;
    float clampedVal;

    // If there's a callback pointer (at this+0x230), call it
    if (*(int *)(thisPtr + 0x230) != 0) {
        // Likely a notification or update function: FUN_00892910(delta, reason)
        FUN_00892910(delta, reason);
    }

    // Add delta to the stored float at this+0x100
    newVal = delta + *(float *)(thisPtr + 0x100);
    oldVal = 0.0f;

    // Clamp newVal to [0.0, DAT_00e44578] (global max value)
    if ((newVal <= 0.0f) || (oldVal = DAT_00e44578, DAT_00e44578 <= newVal)) {
        clampedVal = oldVal;
    } else {
        clampedVal = newVal;
    }

    // Store clamped value at this+0x100
    *(float *)(thisPtr + 0x100) = clampedVal;

    // If this object's class ID (at this+0x54) equals 0x637b907,
    // call another function with the new value
    if (*(int *)(thisPtr + 0x54) == 0x637b907) {
        // FUN_008bcaf0 likely handles specific behavior for that class
        FUN_008bcaf0(clampedVal);
    }

    // Return the stored float (as float10 – extended precision, but cast to float)
    return (float10)*(float *)(thisPtr + 0x100);
}