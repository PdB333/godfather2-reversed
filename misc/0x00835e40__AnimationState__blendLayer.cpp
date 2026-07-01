// FUNC_NAME: AnimationState::blendLayer
void __thiscall AnimationState::blendLayer(AnimationState *this, AnimationState *source, float factor)
{
    // Blend 5 consecutive float fields representing animation parameters (offsets +0x4c,+0x50,+0x54,+0x58,+0x5c)
    *(float *)((char *)this + 0x4c) += *(float *)((char *)source + 0x4c) * factor;
    *(float *)((char *)this + 0x50) += *(float *)((char *)source + 0x50) * factor;
    *(float *)((char *)this + 0x54) += *(float *)((char *)source + 0x54) * factor;
    *(float *)((char *)this + 0x58) += *(float *)((char *)source + 0x58) * factor;
    *(float *)((char *)this + 0x5c) += *(float *)((char *)source + 0x5c) * factor;
}