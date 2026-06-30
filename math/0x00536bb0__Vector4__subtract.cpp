// FUNC_NAME: Vector4::subtract
// Address: 0x00536bb0
// Role: Subtracts another Vector4 (param_1) from this vector and stores the result in output vector (param_2).
// This is a standard 4-component vector subtraction: result = this - other.

void __thiscall Vector4::subtract(float *thisVector, float *otherVector, float *outVector)
{
    float thisX = thisVector[0];
    float thisY = thisVector[1];
    float thisZ = thisVector[2];
    float thisW = thisVector[3];

    float otherX = otherVector[0];
    float otherY = otherVector[1];
    float otherZ = otherVector[2];
    float otherW = otherVector[3];

    outVector[0] = thisX - otherX;
    outVector[1] = thisY - otherY;
    outVector[2] = thisZ - otherZ;
    outVector[3] = thisW - otherW;
}