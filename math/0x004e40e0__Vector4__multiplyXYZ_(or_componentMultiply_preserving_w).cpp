//FUNC_NAME: Vector4::multiplyXYZ (or componentMultiply preserving w)
// Function address: 0x004e40e0
// Multiplies the first three components (x, y, z) of this vector with corresponding components from two source vectors,
// leaving the w component unchanged. This is a component-wise multiplication for 3D vectors with a homogeneous w.
void __thiscall Vector4::multiplyXYZ(const float* src1, const float* src2)
{
    float origW = this->w; // save original w (index 3)
    this->x = src1[0] * src2[0];
    this->y = src1[1] * src2[1];
    this->z = src1[2] * src2[2];
    this->w = src1[3] * src2[3]; // multiply w but then restore original below
    this->w = origW; // restore w to preserve it (only xyz are affected)
}