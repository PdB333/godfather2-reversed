// FUNC_NAME: mirrorVector4D
void mirrorVector4D(float *inVector, float *outVector)
{
    float center = DAT_00e44564; // Global mirror center coordinate (same for x,y,z)
    outVector[0] = center - inVector[0];
    outVector[1] = center - inVector[1];
    outVector[2] = center - inVector[2];
    outVector[3] = inVector[3]; // w component unchanged
}