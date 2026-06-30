// FUNC_NAME: Animated::updateAnimationState
void __fastcall Animated::updateAnimationState()
{
    // Check if animation is in an idle or finished state and there's an active animation controller
    int animState = *(int*)((char*)this + 0x214);          // +0x214: m_animState (enum)
    void* animController = *(void**)((char*)this + 0x290); // +0x290: m_pAnimController
    if ((animState == 0 || animState == 0x48) && animController != 0)
    {
        // Advance or transition the animation
        FUN_004df600();
        // Mark animation as dirty/needs update (bit 12)
        *(uint*)((char*)this + 0x1d0) |= 0x1000;          // +0x1D0: m_nFlags
    }
    // Apply animation updates (e.g., bone transforms)
    FUN_004719e0();
}