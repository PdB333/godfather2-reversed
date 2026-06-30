// FUNC_NAME: Vector4::scaleTo
// Address: 0x004eb240
// Role: Scales a 4-component vector (quaternion/color) by a scalar, storing result in output buffer.
// Source vector is 'this', destination is outVec. Used for linear algebra operations in the EARS engine.

void __thiscall Vector4::scaleTo(float *outVec, float scale)
{
    float x = this[0];  // +0x00: first component
    float y = this[1];  // +0x04: second component
    float z = this[2];  // +0x08: third component
    float w = this[3];  // +0x0C: fourth component (e.g., w in quaternion or alpha in color)

    outVec[0] = scale * x;
    outVec[1] = scale * y;
    outVec[2] = scale * z;
    outVec[3] = scale * w;
}