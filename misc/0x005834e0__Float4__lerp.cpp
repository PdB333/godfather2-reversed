// FUNC_NAME: Float4::lerp
void __thiscall Float4::lerp(const Float4& other, float t, Float4& out) const {
    // this->data points to float array at offset +8, other.data at other +8, out.data at out +8
    float* src1Data = *(float**)((int)this + 8);       // this->data
    float* src2Data = *(float**)((int)&other + 8);     // other.data
    float* destData = *(float**)((int)&out + 8);       // out.data

    destData[0] = (src2Data[0] - src1Data[0]) * t + src1Data[0];
    destData[1] = (src2Data[1] - src1Data[1]) * t + src1Data[1];
    destData[2] = (src2Data[2] - src1Data[2]) * t + src1Data[2];
    destData[3] = (src2Data[3] - src1Data[3]) * t + src1Data[3];
}