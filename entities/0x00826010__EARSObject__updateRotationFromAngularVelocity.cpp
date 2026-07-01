// FUNC_NAME: EARSObject::updateRotationFromAngularVelocity
void __fastcall EARSObject::updateRotationFromAngularVelocity(int this)
{
    // Read angular velocity from +0x84, multiply by global time scale factor
    float angularVelocity = *(float *)(this + 0x84) * DAT_00e445c8; // +0x84: angularVelocity
    double angle = (double)angularVelocity;

    // Compute sin and cos of the angle (likely using internal math functions)
    float sinAngle = (float)FUN_00b99fcb(angle); // sin wrapper
    float cosAngle = (float)FUN_00b99e20(angle); // cos wrapper

    // Read the two components of the rotation axis (or previous orientation) from +0x7c and +0x80
    float axisX = *(float *)(this + 0x7c); // +0x7c: axisX or prevAngle
    float axisY = *(float *)(this + 0x80); // +0x80: axisY or prevAngle2

    // Package the rotation data into a temporary structure (4 floats)
    float local_20 = cosAngle;
    float local_1c = sinAngle;
    float local_18 = axisX; // reinterpreted as float
    float local_14 = axisY; // reinterpreted as float

    // Write the combined rotation data to the output at +0x90 (likely a quaternion or orientation matrix)
    FUN_009d9b60(&local_20, this + 0x90); // copies 16 bytes to this+0x90
}