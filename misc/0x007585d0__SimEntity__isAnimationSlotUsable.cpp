// FUNC_NAME: SimEntity::isAnimationSlotUsable
// Address: 0x007585d0
// Checks if the animation slot at m_animationIndex is valid and not in a blocked state (state != 3)
int __fastcall SimEntity::isAnimationSlotUsable(int this)
{
    // m_pController at +0x10c: pointer to an animation controller object
    int* controllerPtr = *(int**)(this + 0x10c);
    if (controllerPtr == nullptr) {
        return 0; // no controller, cannot use
    }

    uint animationIndex = *(uint*)(this + 0x14c); // m_animationIndex

    // Call virtual function at vtable+8: GetAnimationCount()
    int maxIndex = (*(code**)(*controllerPtr + 8))();

    // Allow only indices strictly less than maxIndex-1 (possibly reserving the last slot)
    if (animationIndex < (uint)(maxIndex - 1)) {
        int state = FUN_00757900(animationIndex); // GetAnimationState(animationIndex)
        if (state != 3) {
            return 1; // usable
        }
    }
    return 0;
}