// FUNC_NAME: Vector4::lerpPreserveW
void __thiscall Vector4::lerpPreserveW(const float* from, const float* to, float t)
{
    // Preserve the fourth component (e.g., w for quaternions or time for positions)
    float w = this->data[3];
    // Linear interpolation of the first three components
    this->data[0] = (to[0] - from[0]) * t + from[0];
    this->data[1] = (to[1] - from[1]) * t + from[1];
    this->data[2] = (to[2] - from[2]) * t + from[2];
    // Restore the original fourth component
    this->data[3] = w;
}