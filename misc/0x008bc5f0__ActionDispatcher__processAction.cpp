// FUNC_NAME: ActionDispatcher::processAction
void __fastcall ActionDispatcher::processAction(void) {
    // +0x50: handle to a target object (e.g., character controller)
    void* target = FUN_008c74d0(*(unsigned int*)((char*)this + 0x50));
    if (target == nullptr) {
        return;
    }

    // +0x5c: action type index
    unsigned int actionType = *(unsigned int*)((char*)this + 0x5c);
    switch (actionType) {
        case 0:   // e.g., start animation
            playActionAnimation();
            return;
        case 1:   // stop animation
            stopActionAnimation();
            return;
        case 2:   // lock movement
            setMovementLocked(true);
            return;
        case 3:   // unlock movement
            setMovementLocked(false);
            return;
        case 4:   // start an effect
        {
            // +0x60: pointer to effect data
            void* data = resolveDataPointer((char*)this + 0x60);
            if (data != nullptr) {
                startEffect(data);
            }
            return;
        }
        case 5:   // stop an effect
        {
            void* data = resolveDataPointer((char*)this + 0x60);
            if (data != nullptr) {
                stopEffect(data);
            }
            return;
        }
        case 6:   // show object
            setVisibility(true);
            return;
        case 7:   // hide object
            setVisibility(false);
            return;
        case 8:   // reset to default state
            resetStateToDefault();
            return;
        case 9:   // clear both disable/pause flags
            // +0x84: flags field – clear bits 10 and 11
            *(unsigned int*)((char*)target + 0x84) &= 0xFFFFF3FF;
            return;
        case 10:  // set "disabled" flag (bit10), clear "paused" (bit11)
            *(unsigned int*)((char*)target + 0x84) |=  0x400;      // set bit10
            *(unsigned int*)((char*)target + 0x84) &= 0xFFFFF7FF;  // clear bit11
            return;
        case 0xB: // clear "disabled", set "paused"
            *(unsigned int*)((char*)target + 0x84) &= 0xFFFFFBFF;  // clear bit10
            *(unsigned int*)((char*)target + 0x84) |=  0x800;      // set bit11
            return;
    }
}