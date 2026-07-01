// FUNC_NAME: Player::updateTimedAction
void __fastcall Player::updateTimedAction(void* this)
{
    char debugFlag;
    char* debugStr;
    int* subObjBase;
    float cooldown;
    uint eventHash = 0xa5975eb2;
    void** eventData = nullptr;
    bool handled;
    int retVal;

    // +0x9c: pointer to a sub-object (e.g., combat state) 
    // +0xb4: timestamp for next action check
    // +0xb0: timestamp for cooldown
    uint* subObjPtr = *(uint**)((char*)this + 0x9c);
    if (subObjPtr == nullptr || subObjPtr == (uint*)0x48) {
        return; // Invalid or no sub-object
    }

    // Check if enough time has passed since last action attempt
    // DAT_00d5ef70 is a constant offset (e.g., g_attackCooldown)
    // DAT_01205214 is global game time (g_currentTime)
    float* timeSinceAction = (float*)((char*)this + 0xb4);
    if (*timeSinceAction + DAT_00d5ef70 <= *DAT_01205214) {
        debugStr = debugGetString(); // FUN_00549a30 - returns debug flag
        if (*debugStr == '\0') {
            return; // Debug flag not set, skip
        }

        // Get base of sub-object (subtract offset 0x48)
        if (subObjPtr == nullptr) {
            subObjBase = nullptr;
        } else {
            subObjBase = (int*)subObjPtr - 0x48;
        }

        // Call virtual function at vtable+0x1a8 (e.g., getCooldownRemaining)
        cooldown = (**(float (__stdcall*)(void*))(*subObjBase + 0x1a8))();
        if (cooldown <= DAT_00d5d934) {
            return; // Cooldown not yet satisfied
        }
    }

    // Check another timer for action delay
    float* timer2 = (float*)((char*)this + 0xb0);
    // DAT_00d5c458 is another constant (e.g., g_attackDelay)
    if (*timer2 + DAT_00d5c458 < *DAT_01205214) {
        debugStr = debugGetString(); // FUN_00549a30
        if (*debugStr != '\0') {
            *(float*)((char*)this + 0xb4) = *DAT_01205214; // Update timestamp
        }
        *(float*)((char*)this + 0xb0) = *DAT_01205214; // Update cooldown timer

        // Get sub-object base again
        if (subObjPtr == nullptr) {
            subObjBase = nullptr;
        } else {
            subObjBase = (int*)subObjPtr - 0x48;
        }

        // Call virtual function at vtable+0x10 (e.g., handleEvent)
        handled = (**(bool (__thiscall*)(void*, uint, void**))(*subObjBase + 0x10))(subObjBase, eventHash, &eventData);
        if (handled && unaff_EBX != 0) {
            // Set up debug drawing? (FUN_007393b0)
            debugDrawSomething(unaff_EBX);

            // Post event message? (FUN_00408a00)
            postMessage(DAT_0112adc8, 0); 

            // Cleanup if needed (FUN_004daf90)
            if (retVal != 0) {
                freeMemory(&retVal);
            }
        }
    }
    return;
}