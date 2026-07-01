// FUNC_NAME: SomeClass::lerpOffset
void __thiscall lerpOffset(int this, int other, float t)
{
    // +0x4c: offset value (e.g., position or rotation component)
    *(float *)(this + 0x4c) = *(float *)(other + 0x4c) * t + *(float *)(this + 0x4c);
}