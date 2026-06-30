// FUNC_NAME: MathUtils::scaleVector3D
void __fastcall MathUtils::scaleVector3D(float *outVector, float *inVector, float scale)
{
    float y = inVector[1];  // +0x04
    float z = inVector[2];  // +0x08
    float w = inVector[3];  // +0x0C (homogeneous component)
    float outW = outVector[3]; // preserve original w component

    outVector[0] = scale * inVector[0];  // x component
    outVector[1] = scale * y;            // y component
    outVector[2] = scale * z;            // z component
    outVector[3] = scale * w;            // w component
    outVector[3] = outW;                 // restore original w (homogeneous coordinate preservation)
}