// FUNC_NAME: Vector4::scaleXYZ
void __fastcall Vector4::scaleXYZ(float *outVec, float *inVec, float scale)
{
    float y = inVec[1];
    float z = inVec[2];
    float w = inVec[3];
    float oldW = outVec[3]; // preserve W component

    outVec[0] = scale * inVec[0];
    outVec[1] = scale * y;
    outVec[2] = scale * z;
    outVec[3] = scale * w;

    outVec[3] = oldW; // restore original W (typically 1.0 for points, 0.0 for vectors)
}