// FUNC_NAME: Math::vectorCrossProduct
// Address: 0x004fc730
// Computes the cross product of two 3D vectors (w component of result is zeroed).
// Parameters:
//   pVecA : Pointer to 4-component vector (first input, reads x,y,z,w)
//   pVecB : Pointer to 4-component vector (second input, reads x,y,z,w) – passed via in_EAX (likely this or register)
//   pResult : Pointer to output 4-component vector
void __thiscall vectorCrossProduct(float* pVecA, float* pResult) {
    float aX = pVecA[0];
    float aY = pVecA[1];
    float aZ = pVecA[2];
    float aW = pVecA[3];               // unused in calculation but preserved in cross product (zeroed)
    float bX = in_EAX[0];              // second vector passed via register (EAX)
    float bY = in_EAX[1];
    float bZ = in_EAX[2];
    float bW = in_EAX[3];
    pResult[0] = aY * bZ - aZ * bY;    // cross.x
    pResult[1] = aZ * bX - aX * bZ;    // cross.y
    pResult[2] = aX * bY - aY * bX;    // cross.z
    pResult[3] = aW * bW - aW * bW;    // = 0.0f
    return;
}