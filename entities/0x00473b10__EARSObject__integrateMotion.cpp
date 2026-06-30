// FUNC_NAME: EARSObject::integrateMotion
void __thiscall EARSObject::integrateMotion(float deltaTime) {
    // Called function: likely quaternion derivative from angular velocity components at offsets 0x40,0x44,0x48
    // Outputs four floats into local array (quaternion derivative or velocity)
    float derivative[4];
    FUN_0056b8a0(*(float*)(this + 0x44), *(float*)(this + 0x40), *(float*)(this + 0x48), derivative);

    // Save original fourth component at +0x3C (likely a scalar or invariant part)
    float savedFourth = *(float*)(this + 0x3C);

    // Euler integration of first three components: new = old + deltaTime * derivative
    // Old values read from +0x20,0x24,0x28; result stored to +0x30,0x34,0x38
    *(float*)(this + 0x30) = deltaTime * derivative[0] + *(float*)(this + 0x20);
    *(float*)(this + 0x34) = deltaTime * derivative[1] + *(float*)(this + 0x24);
    *(float*)(this + 0x38) = deltaTime * derivative[2] + *(float*)(this + 0x28);

    // Fourth component: compute but then restore old value (intentionally preserved)
    *(float*)(this + 0x3C) = deltaTime * derivative[3] + *(float*)(this + 0x2C);
    *(float*)(this + 0x3C) = savedFourth;
}