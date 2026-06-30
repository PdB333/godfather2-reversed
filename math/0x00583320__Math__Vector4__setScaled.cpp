// FUNC_NAME: Math::Vector4::setScaled
void __fastcall Math::Vector4::setScaled(int param_1, const Math::Vector4* source, float scale)
{
    float* srcData = *(float**)(source + 8);  // source->data (offset +0x8)
    float x = srcData[0];
    float y = srcData[1];
    float z = srcData[2];
    float w = srcData[3];
    float* dstData = *(float**)(this + 8);    // this->data (offset +0x8)
    dstData[0] = scale * x;
    dstData[1] = scale * y;
    dstData[2] = scale * z;
    dstData[3] = scale * w;
    dstData[3] = DAT_00e2b1a4;                // overwrite w with constant (likely 1.0f for point)
}