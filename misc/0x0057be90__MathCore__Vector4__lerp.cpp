// FUNC_NAME: MathCore::Vector4::lerp
void __thiscall MathCore::Vector4::lerp(float *from, float *to, float t, float *result) {
    // Linear interpolation of 4-component vector (likely float[4])
    // result = from + (to - from) * t
    result[0] = (to[0] - from[0]) * t + from[0];
    result[1] = (to[1] - from[1]) * t + from[1];
    result[2] = (to[2] - from[2]) * t + from[2];
    result[3] = (to[3] - from[3]) * t + from[3];
}