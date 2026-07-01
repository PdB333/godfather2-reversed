// FUNC_NAME: NPC::processAnimationStateChange
void __thiscall NPC::processAnimationStateChange(int* thisPtr)
{
    int animCtrlPtr = thisPtr[0x1d3]; // +0x74C: pointer to animation controller/state machine
    int resultId = 0xb; // default action ID (11)

    if (animCtrlPtr != 0 && animCtrlPtr != 0x48) {
        int base = (animCtrlPtr == 0) ? 0 : (animCtrlPtr - 0x48); // compensate for known offset
        if (*(char *)(base + 0x1ad) == 0x19) { // animation type: idle/firing?
            resultId = 6;
        }
        else {
            base = (animCtrlPtr == 0) ? 0 : (animCtrlPtr - 0x48);
            if (*(char *)(base + 0x1ad) == 0x1a) { // animation type: run?
                resultId = 8;
            }
            else {
                base = (animCtrlPtr == 0) ? 0 : (animCtrlPtr - 0x48);
                if (*(char *)(base + 0x1ad) == 0x1b) { // animation type: crouch?
                    resultId = 7;
                }
            }
        }
    }

    int handle = 0;
    if (resultId != 0xb) {
        handle = AnimationManager::getAnimation(resultId); // FUN_00705ab0 - returns handle/pointer
    }

    // virtual call at vtable offset 600 (likely playAnimation or attachEffect)
    (thisPtr->vtable[150])(handle);

    if (handle != 0) {
        thisPtr[0x927] |= 0x20000; // +0x249C: set flag for animation active
    }
}