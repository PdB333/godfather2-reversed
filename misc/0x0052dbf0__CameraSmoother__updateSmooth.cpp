// FUNC_NAME: CameraSmoother::updateSmooth
// Address: 0x0052dbf0
// This function performs exponential smoothing of camera state (position, velocity, etc.)
// using a fixed time step. It blends target values from an object (passed via EAX/this)
// into global smoothed state variables.

void CameraSmoother::updateSmooth(void)
{
    // Constants (likely 1.0f for fixed time step)
    const float fixedTimeStep = DAT_00e2b1a4; // +0x00e2b1a4

    // Compute blend factor: alpha = fixedTimeStep / (timeAccumulator + fixedTimeStep)
    float alpha = fixedTimeStep / (DAT_01206720 + fixedTimeStep);
    float oneMinusAlpha = fixedTimeStep - alpha; // Actually 1.0f - alpha, but decompiler shows fixedTimeStep - alpha

    // Smooth velocity (from object offsets +0x20, +0x24)
    DAT_01206710 = *(float *)(this + 0x20) * alpha + oneMinusAlpha * DAT_01206710;
    DAT_01206714 = *(float *)(this + 0x24) * alpha + oneMinusAlpha * DAT_01206714;

    // Smooth position (from object offsets +0x10, +0x14, +0x18, +0x1c)
    DAT_01206700 = (*(float *)(this + 0x10) - DAT_01206700) * alpha + DAT_01206700;
    DAT_01206704 = (*(float *)(this + 0x14) - DAT_01206704) * alpha + DAT_01206704;
    DAT_01206708 = (*(float *)(this + 0x18) - DAT_01206708) * alpha + DAT_01206708;
    DAT_0120670c = (*(float *)(this + 0x1c) - DAT_0120670c) * alpha + DAT_0120670c;

    // Smooth another component (from object offset +0x28)
    DAT_01206718 = *(float *)(this + 0x28) * alpha + oneMinusAlpha * DAT_01206718;

    // Update time accumulator
    DAT_01206720 = DAT_01206720 + fixedTimeStep;
}