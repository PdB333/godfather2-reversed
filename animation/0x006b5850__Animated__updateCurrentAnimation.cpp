// FUNC_NAME: Animated::updateCurrentAnimation
void __thiscall Animated::updateCurrentAnimation(void)
{
    int *pAnimData;
    
    if (this->currentAnimation == 0) {
        // No current animation; check if we should start one
        if ((((this->flags & 1) == 0) && (this->modelData != 0)) &&
            ((pAnimData = getModelData(this->modelData), pAnimData != 0 &&
             ((~(byte)(*(uint *)(pAnimData + 0x84) >> 5) & 1) != 0)))) {
            // Model data exists and animation is not finished (bit5 == 0)
            startAnimation();
            return;
        }
    }
    else {
        // There is a current animation
        if ((((this->flags & 1) == 0) && (this->modelData != 0)) &&
            (pAnimData = getModelData(this->modelData), pAnimData != 0) &&
            ((~(byte)(*(uint *)(pAnimData + 0x84) >> 5) & 1) != 0)) {
            // Conditions still met, animation not finished – keep it
            return;
        }
        // Conditions no longer met or animation finished – stop it
        if (this->currentAnimation != 0) {
            stopAnimation(this->currentAnimation);
            this->currentAnimation = 0;
        }
    }
    return;
}