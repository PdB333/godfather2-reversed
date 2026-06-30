// FUNC_NAME: Vector4::subtractAndStore
// Function at 0x0044c2a0: Computes element-wise subtraction of this vector from another (this - pOther) and stores result in pResult.
void __thiscall Vector4::subtractAndStore(float *pOther, float *pResult) {
    float thisX = this[0];
    float thisY = this[1];
    float thisZ = this[2];
    float thisW = this[3];

    float otherX = pOther[0];
    float otherY = pOther[1];
    float otherZ = pOther[2];
    float otherW = pOther[3];

    pResult[0] = thisX - otherX;
    pResult[1] = thisY - otherY;
    pResult[2] = thisZ - otherZ;
    pResult[3] = thisW - otherW;
}