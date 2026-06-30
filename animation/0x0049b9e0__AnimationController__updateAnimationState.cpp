// FUNC_NAME: AnimationController::updateAnimationState
void AnimationController::updateAnimationState(int slotIndex)
{
    uint state;

    // Read state from animation state array.
    // this+0xB8: pointer to animation state table base.
    // Offset within that table: (slotIndex * 3 + 0x24) * 4 = slotIndex * 12 + 0x90.
    // So each slot occupies 12 bytes; we read the first 4-byte state value.
    state = *(uint *)(*(int *)((char *)this + 0xB8) + (slotIndex * 3 + 0x24) * 4);

    // State values:
    // 6 and 7: intermediate animation states that need handling.
    // 0xC (12): final/completed state – ignore.
    // All other values (0-5, 8-11, etc.) are also passed to the handler.
    if (5 < state)
    {
        if (state < 8)
        {
            handleAnimationState(state);
            return;
        }
        if (state == 0xC)
        {
            return;
        }
    }
    handleAnimationState(state);
}