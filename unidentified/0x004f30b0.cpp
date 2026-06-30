// FUN_004f30b0: Math::vector4ScaleAdd
void __thiscall vector4ScaleAdd(float* thisVector, float* otherVector, float scalar, float* outResult)
{
    // Perform: outResult = scalar * thisVector + otherVector (component-wise for 4 floats)
    outResult[0] = scalar * thisVector[0] + otherVector[0];
    outResult[1] = scalar * thisVector[1] + otherVector[1];
    outResult[2] = scalar * thisVector[2] + otherVector[2];
    outResult[3] = scalar * thisVector[3] + otherVector[3];
}