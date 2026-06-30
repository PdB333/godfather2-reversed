// FUNC_NAME: Animation::isPlaying
// Address: 0x007197e0
// Checks if an animation is currently playing.
// The animation state is stored at offset +0x330.
// State value 0x48 (72) likely represents a finished/stopped state.
// If state is valid (non-zero and not finished), it verifies via isAnimationRunning().

bool __thiscall Animation::isPlaying(void)
{
    // +0x330: Current animation state (e.g., playing, paused, finished)
    int animState = *(int *)((int)this + 0x330);

    if (animState != 0 && animState != 0x48) {
        // Check if the animation is actually running (not paused or transitioning)
        if (isAnimationRunning()) {
            return true;
        }
    }
    return false;
}