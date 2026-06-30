// FUNC_NAME: Vector4::addScaled
void __thiscall Vector4::addScaled(const float* otherVector, float scalar, float* outVector)
{
    // outVector = otherVector + scalar * this (component-wise)
    outVector[0] = scalar * this[0] + otherVector[0];
    outVector[1] = scalar * this[1] + otherVector[1];
    outVector[2] = scalar * this[2] + otherVector[2];
    outVector[3] = scalar * this[3] + otherVector[3];
}