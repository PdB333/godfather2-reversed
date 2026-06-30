// FUNC_NAME: AnimationController::updateAnimationFromState
void __thiscall AnimationController::updateAnimationFromState() {
    // Read the current animation state ID from a nested structure
    // this->+0x18 points to some state manager, offset 0x2004 holds the state ID
    int stateId = *(int*)(*(int*)((char*)this + 0x18) + 0x2004);

    // Only update if the state is valid and not the "idle/none" state (0x48)
    if (stateId != 0 && stateId != 0x48) {
        // Get a handle for the animation set using the special invalid index (-1)
        int animSetHandle = getAnimationSetHandle(0xFFFFFFFF);

        // Store the handle at this->+0x358, and clear a counter at this->+0x35C
        *(int*)((char*)this + 0x358) = animSetHandle;
        *(int*)((char*)this + 0x35C) = 0;

        // Create a new animation instance from the set handle and store it at this->+0x354
        int animInstance = createAnimationInstance(animSetHandle);
        *(int*)((char*)this + 0x354) = animInstance;
    }
}