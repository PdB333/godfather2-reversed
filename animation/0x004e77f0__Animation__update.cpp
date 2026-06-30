//FUNC_NAME: Animation::update
void __thiscall Animation::update(float deltaTime)
{
    // Get the animation definition pointer
    AnimationDef* def = *(AnimationDef**)(this + 0x24);
    float defStartTime = *(float*)(def + 0x18); // +0x18: start time or duration

    // Get thread-local context (FS:[0x2c] -> pointer to some per-thread structure)
    ThreadContext* threadCtx = *(ThreadContext**)(__readfsdword(0x2c));

    // Check if current time is within a global threshold range
    if ((gMinTime < defStartTime) && (defStartTime < *(float*)(this + 0x28))) {
        uint* flagPtr = (uint*)(*(int*)(threadCtx->buffer + 8) + *(int*)(this + 0x10));
        *flagPtr |= 1; // Set a flag indicating something
    }

    int* eventQueue = gEventQueue; // DAT_01206880
    def = *(AnimationDef**)(this + 0x24);

    // Check if the flag we just set is not set (i.e., condition not triggered)
    if ((*(byte*)(*(int*)(threadCtx->buffer + 8) + *(int*)(this + 0x10)) & 1) == 0) {
        // Flag not set
        if ((*(uint*)(def + 0x14) & 0x10) != 0) {
            // Definition has bit 0x10 set (e.g., event on completion)
            if (((((*(uint*)(def + 0x14) & 0x200) == 0) || (*(byte*)(def + 0x11) == 0)) ||
                 (gSomeFlag == 0)) || (((byte)gSomeFlag & *(byte*)(def + 0x11)) != 0)) {
                **(void***)(eventQueue + 0x14) = &eventCallback1; // PTR_LAB_01124fd0
            } else {
                **(void***)(eventQueue + 0x14) = &eventCallback2; // PTR_LAB_01124fe4
            }
            // Push this animation onto the event queue
            int* queuePtr = (int*)(eventQueue + 0x14);
            *queuePtr = *queuePtr + 4;
            *(int*)*queuePtr = (int)this;
            *queuePtr = *queuePtr + 4;
        }

        // Update current time
        float newTime = *(float*)(this + 0x28) + deltaTime;
        *(float*)(this + 0x28) = newTime;

        float currentValue;
        if ((*(int*)(this + 0x34) == 1) && (*(int*)(this + 0x38) == 0)) {
            // Looping animation (loop mode 1, loop count 0)
            float clampMin = *(float*)(def + 0x38); // +0x38: min clamp value
            float v1 = newTime * *(float*)(def + 0x2c) + *(float*)(def + 0x28); // rate1 * time + base
            float v2 = newTime * *(float*)(def + 0x34) + *(float*)(def + 0x30); // rate2 * time + base2
            if (v1 < v2) {
                v2 = v1;
            }
            if ((clampMin <= v2) && (clampMin = v2, *(float*)(def + 0x3c) < v2)) {
                clampMin = *(float*)(def + 0x3c); // +0x3c: max clamp value
            }
            currentValue = clampMin;
        } else {
            // Non-looping: compute via external function
            FUN_004ebc00(*(int*)(this + 0x4), 0);
            currentValue = newTime;
        }

        // Clamp to zero
        if (currentValue < 0.0f) {
            currentValue = 0.0f;
        }
        *(float*)(this + 0x2c) = currentValue;
    } else {
        // Flag was set, and definition has bit 0x10 set
        if ((*(byte*)(def + 0x14) & 0x10) != 0) {
            // Push event with callback2
            int* queuePtr = (int*)(gEventQueue + 0x14);
            **(void***)(gEventQueue + 0x14) = &eventCallback2;
            *queuePtr = *queuePtr + 4;
            *(int*)*queuePtr = (int)this;
            *queuePtr = *queuePtr + 4;
            return;
        }
    }
}