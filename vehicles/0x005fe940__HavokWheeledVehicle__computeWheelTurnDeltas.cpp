// FUNC_NAME: HavokWheeledVehicle::computeWheelTurnDeltas
// Function address: 0x005fe940
// Computes steering or rotation deltas for left and right wheels based on current and target angles
// Returns 1 if both wheel pointers are valid, else 0
// Inputs: this (HavokWheeledVehicle*), output float pointers for leftDelta, rightDelta, rotationDelta (or similar)
// Global constants: s_fClampLow, s_fClampHigh, s_fAdjustment (likely configurable threshold/backlash values)

float g_fClampLow = DAT_00e44588;   // lower clamp bound
float g_fClampHigh = DAT_00e2afac;  // upper clamp bound
float g_fAdjustment = DAT_00e2a848; // hysteresis adjustment step

int __thiscall HavokWheeledVehicle::computeWheelTurnDeltas(void* this_, float* outLeftDelta, float* outRightDelta, float* outRotationDelta)
{
    // Check if left and right wheel objects exist (pointers at +0x94 and +0x9C)
    if (*(int*)((char*)this_ + 0x94) == 0 || *(int*)((char*)this_ + 0x9C) == 0)
    {
        return 0;  // missing wheel reference
    }

    // Compute left wheel delta: difference between current and target? (positions at +0xC4 and +0xC0)
    float leftDelta = *(float*)((char*)this_ + 0xC4) - *(float*)((char*)this_ + 0xC0);
    if (leftDelta < 0.0f)
    {
        leftDelta = 0.0f;  // clamp negative to zero
    }
    *outLeftDelta = leftDelta;

    // Compute right wheel delta: difference between +0xFC and +0xF4 (target - current)
    float rightDelta = *(float*)((char*)this_ + 0xFC) - *(float*)((char*)this_ + 0xF4);
    // Apply hysteretic clamping: if delta exceeds upper bound, reduce by adjustment; if below lower bound, increase by adjustment
    if (rightDelta > g_fClampHigh)
    {
        rightDelta = rightDelta - g_fAdjustment;
    }
    else if (rightDelta < g_fClampLow)
    {
        rightDelta = rightDelta + g_fAdjustment;
    }
    *outRightDelta = rightDelta;

    // Compute rotation delta (e.g., steering wheel angle): difference between +0x108 and +0x100
    float rotationDelta = *(float*)((char*)this_ + 0x108) - *(float*)((char*)this_ + 0x100);
    if (g_fClampHigh < rotationDelta)
    {
        *outRotationDelta = rotationDelta - g_fAdjustment;
        return 1;
    }
    if (rotationDelta < g_fClampLow)
    {
        rotationDelta = rotationDelta + g_fAdjustment;
    }
    *outRotationDelta = rotationDelta;
    return 1;
}