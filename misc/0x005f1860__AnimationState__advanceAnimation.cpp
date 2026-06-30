// FUNC_NAME: AnimationState::advanceAnimation
void __thiscall AnimationState::advanceAnimation(AnimationState* this, AnimationDriver* driver) {
    byte speedByte;
    
    // Check: driver valid, this valid, animation clip exists, state not finished (4)
    if (driver != 0 && this != 0 && this->pAnimationClip != 0 && this->state != 4) {
        // Decide how to set targetTime based on animation clip's name[1]
        if (this->pAnimationClip->name[1] == '\0') {
            // Empty clip name: copy currentTime directly
            this->targetTime = this->currentTime;
        } else {
            // Non‑empty name: call external compute function
            FUN_005f20c0(); // likely computeTargetTime
        }
        
        speedByte = driver->speedByte; // byte at +0x03 of driver
        this->flags |= 1;               // set playing flag at +0x6C
        this->targetTime += speedByte * 8; // advance time based on speed
        
        FUN_005e5200(1); // setAnimationActive(true)
        FUN_005dbc10();  // finalizeAnimationUpdate
    }
}