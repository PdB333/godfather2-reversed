// FUNC_NAME: Sentient::getCurrentAnimationId
unsigned char __fastcall Sentient::getCurrentAnimationId(Sentient* this) {
    int animationComponent = *(int*)((char*)this + 0x74c); // +0x74c: pointer to AnimationComponent or model instance
    unsigned char result = 0xff;                          // default: no animation
    if (animationComponent != 0 && animationComponent != 0x48) { // 0x48 = possibly "invalid" or "null" sentinel
        if ((*(unsigned int*)((char*)this + 0x8e0) >> 10 & 1) != 0) { // bit 10 at +0x8e0: animation active flag?
            result = *(unsigned char*)(animationComponent + 0x165);    // +0x165: current animation ID byte
        }
    }
    return result;
}