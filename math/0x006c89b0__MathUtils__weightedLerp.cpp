//FUNC_NAME: MathUtils::weightedLerp
float __thiscall MathUtils::weightedLerp(int this, float from, float to, float weightScale)
{
    // +0x60: stored blend factor (e.g., animation blend weight)
    float factor = *(float *)(this + 0x60);
    return (to - from) * factor * weightScale + from;
}