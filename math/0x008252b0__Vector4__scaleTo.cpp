// FUNC_NAME: Vector4::scaleTo
// Address: 0x008252b0
// Scales this vector by a scalar and stores result in output vector

void __thiscall Vector4::scaleTo(float *outVec, float scalar) {
    outVec[0] = this->x * scalar; // +0x00
    outVec[1] = this->y * scalar; // +0x04
    outVec[2] = this->z * scalar; // +0x08
    outVec[3] = this->w * scalar; // +0x0C
}