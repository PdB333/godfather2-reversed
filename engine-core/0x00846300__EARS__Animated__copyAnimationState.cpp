// FUNC_NAME: EARS::Animated::copyAnimationState
void __thiscall EARS::Animated::copyAnimationState(int thisPtr) {
    struct AnimationStateData { // 12 bytes
        uint32_t stateId;   // +0x00
        uint32_t param;     // +0x04
        uint8_t flags;      // +0x08 (padding?)
    };

    AnimationStateData state;
    if ((*(uint32_t *)(thisPtr + 0x118) & 0x7800) != 0) {
        state.stateId = *(uint32_t *)(thisPtr + 0x7c); // +0x7c: secondary animation state ID
        state.param = 0;
        state.flags = 0;
        FUN_00408a00(&state, 0); // apply animation state (clear flags)
        return;
    }
    state.stateId = *(uint32_t *)(thisPtr + 0x74); // +0x74: primary animation state ID
    state.param = 0;
    state.flags = 0;
    FUN_00408a00(&state, 0);
    return;
}