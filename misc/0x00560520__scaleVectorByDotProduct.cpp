// FUNC_NAME: scaleVectorByDotProduct
void __fastcall scaleVectorByDotProduct(float *outVector, float *inVector, int objectPtr)
{
    // objectPtr + 0x18 is a pointer to a sub-object (e.g., rigid body)
    int subObject = *(int *)(objectPtr + 0x18);
    // subObject + 0x1a0 is a 3-component direction vector (x, y, z)
    float *direction = (float *)(subObject + 0x1a0);

    // Compute dot product of input vector with the direction
    float dot = inVector[0] * direction[0] +
                inVector[1] * direction[1] +
                inVector[2] * direction[2];

    // Scale the input vector by (dot * globalConstant)
    float scale = dot * DAT_00e2cd14;
    outVector[0] = inVector[0] * scale;
    outVector[1] = inVector[1] * scale;
    outVector[2] = inVector[2] * scale;
    outVector[3] = inVector[3] * scale; // also scale the w component
}