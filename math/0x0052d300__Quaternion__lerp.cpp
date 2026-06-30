// FUNC_NAME: Quaternion::lerp
void __thiscall Quaternion::lerp(const float* to, float t, float* outResult)
{
    // Lerp between this (source) quaternion and 'to' quaternion by factor t
    outResult[0] = (to[0] - this[0]) * t + this[0]; // x
    outResult[1] = (to[1] - this[1]) * t + this[1]; // y
    outResult[2] = (to[2] - this[2]) * t + this[2]; // z
    outResult[3] = (to[3] - this[3]) * t + this[3]; // w
}