// FUNC_NAME: Vector4::scaleInto
void __thiscall Vector4::scaleInto(float *outVec, float scalar) {
    // in_EAX is 'this' pointing to source Vector4 (x, y, z, w at offsets 0, 4, 8, 12)
    float srcX = this->x;
    float srcY = this->y;
    float srcZ = this->z;
    float srcW = this->w;
    outVec[0] = scalar * srcX;
    outVec[1] = scalar * srcY;
    outVec[2] = scalar * srcZ;
    outVec[3] = scalar * srcW;
}